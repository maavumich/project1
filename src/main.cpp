#include "deps/SimWindow.hpp"
#include "deps/Constants.hpp"

using namespace std;
using glm::vec2;

// Write event handler function prototypes here
void updateRoombaLocation(Roomba& roomba);
void vehicleMoveForward(Vehicle& vehicle);
void vehicleMoveBackward(Vehicle& vehicle);
void vehicleMoveLeftward(Vehicle& vehicle);
void vehicleMoveRightward(Vehicle& vehicle);
void vehicleYawLeft(Vehicle& vehicle);
void vehicleYawRight(Vehicle& vehicle);
void vehicleStopMoveForward(Vehicle& vehicleStop);
void vehicleStopMoveBackward(Vehicle& vehicleStop);
void vehicleStopMoveLeftward(Vehicle& vehicleStop);
void vehicleStopMoveRightward(Vehicle& vehicleStop);

int main(int argc, char** argv)
{
	auto app = Gtk::Application::create(argc, argv, "org.maav.training.simulation");
	SimWindow win{};

	// Attach event handlers here
	win.setRoombaUpdateFunc(updateRoombaLocation);

	win.createRoomba(5, 5, 0, 0.75, {0.8f,0.f,0.f});
	win.createRoomba(7, 7, 0, 0.75, {0.8f,0.f,0.f});
	win.createRoomba(7, 3, 0, 0.75, {0.8f,0.f,0.f});

	// Attach Key Bindings
	win.attachEventHandler(GDK_KEY_w, vehicleMoveForward);
	win.attachEventHandler(GDK_KEY_s, vehicleMoveBackward);
	win.attachEventHandler(GDK_KEY_a, vehicleMoveLeftward);
	win.attachEventHandler(GDK_KEY_d, vehicleMoveRightward);
	win.attachEventHandler(GDK_KEY_q, vehicleYawLeft);
	win.attachEventHandler(GDK_KEY_e, vehicleYawRight);
	// Stop vehicle movement when key is released
	win.attachEventStopHandler(GDK_KEY_w, vehicleStopMoveForward);
	win.attachEventStopHandler(GDK_KEY_s, vehicleStopMoveBackward);
	win.attachEventStopHandler(GDK_KEY_a, vehicleStopMoveLeftward);
	win.attachEventStopHandler(GDK_KEY_d, vehicleStopMoveRightward);
	win.attachEventHandler(GDK_KEY_q, vehicleYawLeft);
	win.attachEventHandler(GDK_KEY_e, vehicleYawRight);

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
	vec2 vel = vehicle.getVelocity() + vec2{0.f, 3.f};
	vehicle.setVelocity(vel);
}
void vehicleMoveBackward(Vehicle& vehicle)
{
	vec2 vel = vehicle.getVelocity() + vec2{0.f, -3.f};
	vehicle.setVelocity(vel);
}
void vehicleMoveLeftward(Vehicle& vehicle)
{
	vec2 vel = vehicle.getVelocity() + vec2{-3.f, 0.f};
	vehicle.setVelocity(vel);
}
void vehicleMoveRightward(Vehicle& vehicle)
{
	vec2 vel = vehicle.getVelocity() + vec2{3.f, 0.f};
	vehicle.setVelocity(vel);
}
void vehicleYawLeft(Vehicle& vehicle)
{
	vehicle.setYaw(vehicle.getYaw() + Constants::pi / 180);
}
void vehicleYawRight(Vehicle& vehicle)
{
	vehicle.setYaw(vehicle.getYaw() - Constants::pi / 180);
}
void vehicleStopMoveForward(Vehicle& vehicle)
{
	vec2 vel = vehicle.getVelocity() - vec2{0.f, 3.f};
	vehicle.setVelocity(vel);
}
void vehicleStopMoveBackward(Vehicle& vehicle)
{
	vec2 vel = vehicle.getVelocity() - vec2{0.f, -3.f};
	vehicle.setVelocity(vel);
}
void vehicleStopMoveLeftward(Vehicle& vehicle)
{
	vec2 vel = vehicle.getVelocity() - vec2{-3.f, 0.f};
	vehicle.setVelocity(vel);
}
void vehicleStopMoveRightward(Vehicle& vehicle)
{
	vec2 vel = vehicle.getVelocity() - vec2{3.f, 0.f};
	vehicle.setVelocity(vel);
}
