#include "SimWindow.hpp"
#include <limits.h>
#include <unistd.h>
#include <thread>
#include <sstream>

using namespace std;

RenderArea::RenderArea(shared_ptr<Simulator> sim_in)
: ObjectBase{nullptr}, sim{sim_in}
{
	set_required_version(3, 3); // Require OpenGL 3.3

	// For placeholders _1 and _2
	using namespace std::placeholders;

	// Connect relevant signals to functions defined in this class
	signal_map().connect(bind(&RenderArea::on_map, this));
	signal_unmap().connect(bind(&RenderArea::on_unmap, this));
	signal_resize().connect(bind(&RenderArea::on_resize, this, _1, _2));
	signal_render().connect([this](const Glib::RefPtr<Gdk::GLContext>& ctx) {
		return on_render(ctx);
	});
}

void RenderArea::on_map()
{
	make_current();
	throw_if_error();
	renderer = make_unique<Renderer>();
	renderer->resize({get_width(), get_height()});
	sim->createVehicle(renderer->getProgram());
	for(auto i : roombaInfo) {
		sim->createRoomba(i.x, i.y, i.yaw, i.radius, renderer->getProgram(),
			i.color.data());
	}
	for(auto i : obstacleInfo) {
		sim->createObstacle(i.x, i.y, i.yaw, i.radius, renderer->getProgram(),
			i.color.data());
	}
	for(auto i : rectangleInfo) {
		renderer->addRectangle(i.x, i.y, i.yaw, i.color.data(), renderer->getProgram(),
			i.width, i.height);
	}
}

void RenderArea::on_unmap()
{
	make_current();
	renderer.reset();
}

void RenderArea::on_resize(int width, int height)
{
	make_current();
	if(renderer) renderer->resize({width, height});
}

bool RenderArea::on_render(const Glib::RefPtr<Gdk::GLContext>&)
{
	if(renderer) {
		renderer->render(sim->getVehicle(), sim->getRoombaList(),
				 sim->getObstacleList());
		attach_buffers();
		renderer->blit();
	}
	return true;
}

void RenderArea::queueRoombaConstruction(EntityInfo cinfo)
{
	roombaInfo.push_back(cinfo);
}

void RenderArea::queueObstacleConstruction(EntityInfo cinfo)
{
	obstacleInfo.push_back(cinfo);
}

void RenderArea::queueGridLineConstruction(RectangleInfo cinfo)
{
	rectangleInfo.push_back(cinfo);
}
////////////////////////////////////////Window//////////////////////////////////////////////////////

SimWindow::SimWindow() : sim{make_shared<Simulator>()}, renderArea{sim}
{
	set_default_size(800,800);
	set_title("Spooky Thing"); // Credit for name: @dziedada

	Glib::signal_timeout().connect([this]() {
		if(sim->simulate(SIMULATION_DT_MS)) {
			string path = getDir() + "deps/";
			stringstream score;
			score << sim->getScore();
			cerr << "Your score: " << score.str() << endl;
			string winscript = path + "win_script.sh -s ";
			winscript += score.str() + " &";
			system(winscript.c_str());
			get_application()->quit();
		}

		renderArea.queue_render();
		return true;
	}, SIMULATION_DT_MS);

	renderArea.set_vexpand(true);
	renderArea.set_hexpand(true);

	//Attach grid objects:
	//	The RenderArea acts as the initial object attached to the grid. All other objects
	//	must be attached relative to this using one of the attach*() function of Gtk::Grid.
	//	These functons are documented online (search fot Gtk::Grid). The last two parameters
	//	of the attach function describe how many grid lines that the RenderArea takes up in
	//	the x and y directions in that order.
	layoutGrid.attach(renderArea, 0, 0, 1, 1);

	// Add the grid to this window
	add(layoutGrid);
	show_all_children();

	// Signal handler for key release
	signal_key_press_event().connect(
		sigc::mem_fun(*this, &SimWindow::on_key_press), false);
	signal_key_release_event().connect(
		sigc::mem_fun(*this, &SimWindow::on_key_release), false);

	// The proper event masks must be added before this window can respond to the corresponding
	// event. Multiple masks can be added using the bitwise or operator as such:
	// 	add_events(Gdk::KEY_RELEASE_MASK | Gdk::KEY_PRESS_MASK | Gdk::SCROLL_MASK)
	add_events(Gdk::KEY_RELEASE_MASK | Gdk::KEY_PRESS_MASK);
}

SimWindow::~SimWindow()
{
	timeout.disconnect();
}

bool SimWindow::on_key_press(GdkEventKey* e)
{
	if(e->keyval == GDK_KEY_Escape) {
		get_application()->quit();
	} else {
		auto func = eventHandlers.find(e->keyval);
		auto pressed = keyRegistrar.find(e->keyval);
		if(func != eventHandlers.end() && pressed != keyRegistrar.end() && !pressed->second) {
			func->second(sim->getVehicle()[0]);
			pressed->second = true;
		}
	}
	return true;
}

bool SimWindow::on_key_release(GdkEventKey* e)
{
	auto func = eventStopHandlers.find(e->keyval);
	auto pressed = keyRegistrar.find(e->keyval);
	if(func != eventStopHandlers.end() && pressed != keyRegistrar.end()) {
		func->second(sim->getVehicle()[0]);
		pressed->second = false;
	}
	return true;
}

bool SimWindow::attachEventHandler(int key, const VehiCallback& func)
{
	keyRegistrar.insert(pair<int, bool>{key, false});
	return get<1>(eventHandlers.insert(
		pair<int, VehiCallback>{key, func}));
}

bool SimWindow::attachEventStopHandler(int key, const VehiCallback& func)
{
	return get<1>(eventStopHandlers.insert(
		pair<int, VehiCallback>{key, func}));
}

void SimWindow::createRoomba(float x, float y, float yaw, float radius, vector<float> color)
{
	renderArea.queueRoombaConstruction({x, y, yaw, radius, color});
}

void SimWindow::createObstacle(float x, float y, float yaw, float radius, vector<float> color)
{
	renderArea.queueObstacleConstruction({x, y, yaw, radius, color});
}

void SimWindow::createGridLine(float x, float y, float yaw, std::vector<float> color, float height,
		float width)
{
	renderArea.queueGridLineConstruction({x, y, yaw, height, width, color});
}

void SimWindow::setGreenLinePosition(LinePosition newPos)
{
	sim->setGreenLinePosition(newPos);
}

void SimWindow::setRedLinePosition(LinePosition newPos)
{
	sim->setRedLinePosition(newPos);
}

void SimWindow::setRoombaUpdateFunc(RoombaCallback func)
{
	sim->setRoombaUpdateFunc(func);
}

void SimWindow::setObstacleUpdateFunc(ObstCallback func)
{
	sim->setObstacleUpdateFunc(func);
}
string SimWindow::getDir()
{
	char pwd[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe", pwd, PATH_MAX);
	string dir(pwd, (count>0) ? count : 0);
	dir = dir.substr(0, dir.find_last_of("/")+1);
	return dir;
}
