#include "deps/SimWindow.hpp"
#include "deps/Constants.hpp"

using namespace std;

// Write event handler function prototypes here
void updateRoombaLocation(Roomba& roomba);
void vehicleMoveForward(Vehicle& vehicle);
void vehicleMoveBackward(Vehicle& vehicle);
void vehicleMoveLeftward(Vehicle& vehicle);
void vehicleMoveRightward(Vehicle& vehicle);
void vehicleYawLeft(Vehicle& vehicle);
void vehicleYawRight(Vehicle& vehicle);

int main(int argc, char** argv)
{
	auto app = Gtk::Application::create(argc, argv, "org.maav.training.simulation");
	SimWindow win{};

	// Attach event handlers here
	win.setRoombaUpdateFunc(updateRoombaLocation);

	win.createRoomba(5, 5, 0, 0.75, {0.8f,0.f,0.f});

	// Attach Key Bindings
	win.attachHoldHandler(GDK_KEY_w, vehicleMoveForward);
	win.attachHoldHandler(GDK_KEY_s, vehicleMoveBackward);
	win.attachHoldHandler(GDK_KEY_a, vehicleMoveLeftward);
	win.attachHoldHandler(GDK_KEY_d, vehicleMoveRightward);
	win.attachHoldHandler(GDK_KEY_q, vehicleYawLeft);
	win.attachHoldHandler(GDK_KEY_e, vehicleYawRight);

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

void vehicleMoveForward(Vehicle& vehicle)
{
	vehicle.setPosition(vehicle.getXPos(), vehicle.getYPos() + 0.05);
}
void vehicleMoveBackward(Vehicle& vehicle)
{
	vehicle.setPosition(vehicle.getXPos(), vehicle.getYPos() - 0.05);
}
void vehicleMoveLeftward(Vehicle& vehicle)
{
	vehicle.setPosition(vehicle.getXPos() - 0.05, vehicle.getYPos());
}
void vehicleMoveRightward(Vehicle& vehicle)
{
	vehicle.setPosition(vehicle.getXPos() + 0.05, vehicle.getYPos());
}
void vehicleYawLeft(Vehicle& vehicle)
{
	vehicle.setYaw(vehicle.getYaw() + Constants::pi / 180);
}
void vehicleYawRight(Vehicle& vehicle)
{
	vehicle.setYaw(vehicle.getYaw() - Constants::pi / 180);
}
