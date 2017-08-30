#include "deps/SimWindow.hpp"
#include "deps/Constants.hpp"

using namespace std;

// Write event handler function prototypes here
void updateRoombaLocation(Roomba& roomba);

int main(int argc, char** argv)
{
	auto app = Gtk::Application::create(argc, argv, "org.maav.training.simulation");
	SimWindow win{};

	// Attach event handlers here
	win.setRoombaUpdateFunc(updateRoombaLocation);
	vector<float> color = {0.8f,0.2f,0.8f};
	win.createRoomba(2.f, 2.f, 0.f, 0.75f, color);
	win.createRoomba(10.f, 10.f, 0.f, 0.75f, color);
	win.createRoomba(10.f, 0.f, 0.f, 0.75f, color);
	win.createRoomba(0.f, 10.f, 0.f, 0.75f, color);
	win.createObstacle(5.f,5.f,0.f,0.75f,color);
	win.setObstacleUpdateFunc([](Obstacle&){});
	return app->run(win);
}

// Write event handler function implementations here

// Function Pointers for simulator class, passed to simwindow and used to create
// Roomba and Obstacle

// Modifies: Roomba object
// Effects:  Rotates roomba
void updateRoombaLocation(Roomba& roomba)
{
	roomba.setYaw(roomba.getYaw() + Constants::pi / 180);
	//roomba.setPosition(roomba.getXPos() + 0.1f, roomba.getYPos());
}
