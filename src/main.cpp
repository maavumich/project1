#include "deps/SimWindow.hpp"
#include "deps/Constants.hpp"

using namespace std;
using std::cos;
using std::sin;

// Write event handler function prototypes here
void updateRoombaLocation(Roomba& roomba);
void vehicleMoveForward(Vehicle& vehicle);
void vehicleMoveBackward(Vehicle& vehicle);
void vehicleMoveLeftward(Vehicle& vehicle);
void vehicleMoveRightward(Vehicle& vehicle);

constexpr float VEHICLE_SPEED = 1.f;

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

	return app->run(win);
}

// Write event handler function implementations here

// Function Pointers for simulator class, passed to simwindow and used to create
// Roomba and Obstacle

// Modifies: Roomba object
// Effects:  Rotates roomba
void updateRoombaLocation(Roomba& roomba)
{
	//roomba.setYaw(roomba.getYaw() + Constants::pi / 180);
	//roomba.setPosition(roomba.getXPos() + 0.1f, roomba.getYPos());
	float theta = roomba.getYawPhysics();
	float speed = roomba.getSpeed() / SIMULATION_DT_MS;	

	roomba.setPosition(roomba.getXPos() +  speed * cos(theta),
		roomba.getYPos() + speed * sin(theta));
}

void vehicleMoveForward(Vehicle& vehicle)
{
	vehicle.setYaw(Constants::pi / 2);
	vehicle.setSpeed(VEHICLE_SPEED);

	float theta = vehicle.getYaw();
	float speed = vehicle.getSpeed() / SIMULATION_DT_MS;

	vehicle.setPosition(vehicle.getXPos() +  speed * cos(theta),
		vehicle.getYPos() + speed * sin(theta));
}
void vehicleMoveBackward(Vehicle& vehicle)
{
	vehicle.setYaw(-1 * Constants::pi / 2);
	vehicle.setSpeed(VEHICLE_SPEED);

	float theta = vehicle.getYaw();
	float speed = vehicle.getSpeed() / SIMULATION_DT_MS;

	vehicle.setPosition(vehicle.getXPos() +  speed * cos(theta),
		vehicle.getYPos() + speed * sin(theta));
}
void vehicleMoveLeftward(Vehicle& vehicle)
{
	vehicle.setYaw(Constants::pi);
	vehicle.setSpeed(VEHICLE_SPEED);

	float theta = vehicle.getYaw();
	float speed = vehicle.getSpeed() / SIMULATION_DT_MS;

	vehicle.setPosition(vehicle.getXPos() +  speed * cos(theta),
		vehicle.getYPos() + speed * sin(theta));
}
void vehicleMoveRightward(Vehicle& vehicle)
{
	vehicle.setYaw(0);
	vehicle.setSpeed(VEHICLE_SPEED);

	float theta = vehicle.getYaw();
	float speed = vehicle.getSpeed() / SIMULATION_DT_MS;

	vehicle.setPosition(vehicle.getXPos() +  speed * cos(theta),
		vehicle.getYPos() + speed * sin(theta));
}
