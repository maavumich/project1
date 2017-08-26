#include "SimWindow.hpp"

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
		renderer->blit();
	}
	return true;
}

Program* RenderArea::getProgram()
{
	return renderer->getProgram();
}

////////////////////////////////////////Window//////////////////////////////////////////////////////

SimWindow::SimWindow() : sim{make_shared<Simulator>()}, renderArea{sim}
{
	sim = make_shared<Simulator>();
	set_default_size(800,600);
	set_title("Spooky Thing"); // Credit for name: @dziedada

	Glib::signal_timeout().connect([this]() {
		for(const auto& handler : holdHandlers) {
			sim->addAction(handler.second.first);
		}
		sim->simulate(SIMULATION_DT_MS);
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
	const auto& act = holdHandlers.find(e->keyval);
	if(act != holdHandlers.end()) {
		act->second.second = true;

	}
	return true;
}

bool SimWindow::on_key_release(GdkEventKey* e)
{
	const auto& act = holdHandlers.find(e->keyval);
	if(act != holdHandlers.end()) {
		act->second.second = false;
	}
	return true;
}

bool SimWindow::attachHoldHandler(int key, VehiCallback func)
{
	return get<1>(holdHandlers.insert(
		pair<int, pair<VehiCallback, bool> >(key, {func, false})));
}

void SimWindow::createRoomba(float x, float y, float yaw, float radius, vector<float> color)
{
	sim->createRoomba(x, y, yaw, radius, &renderArea.getProgram(), color.data());
}
