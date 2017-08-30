#include "deps/SimWindow.hpp"
#include "deps/Constants.hpp"

using namespace std;
using std::cos;
using std::sin;

// Write event handler function prototypes here
void updateRoombaLocation(Roomba& roomba);
void updateObstacleLocation(Obstacle& obstacle);
void vehicleMoveForward(Vehicle& vehicle);
void vehicleMoveBackward(Vehicle& vehicle);
void vehicleMoveLeftward(Vehicle& vehicle);
void vehicleMoveRightward(Vehicle& vehicle);
void vehicleYawLeft(Vehicle& vehicle);
void vehicleYawRight(Vehicle& vehicle);

// Create the grid lines function
void createGridLines(SimWindow& win);
void createRoombas(SimWindow& win);
void createObstacles(SimWindow& win);


constexpr float VEHICLE_SPEED = 1.f;

int main(int argc, char** argv)
{
	auto app = Gtk::Application::create(argc, argv, "org.maav.training.simulation");
	// Create the sim window object
	SimWindow win{};

	// Attach event handlers here
	win.setRoombaUpdateFunc(updateRoombaLocation);
	// Attach Key Bindings
	win.attachHoldHandler(GDK_KEY_w, vehicleMoveForward);
	win.attachHoldHandler(GDK_KEY_s, vehicleMoveBackward);
	win.attachHoldHandler(GDK_KEY_a, vehicleMoveLeftward);
	win.attachHoldHandler(GDK_KEY_d, vehicleMoveRightward);
	// Set up the arena
	createGridLines(win);
	createRoombas(win);
	createObstacles(win);
	win.setObstacleUpdateFunc(updateObstacleLocation);
	return app->run(win);
}

void createGridLines(SimWindow& win)
{
	float height = 10.f;
	float width = 0.1f;
	std::vector<float> color = {0.85f,0.8f,0.77f};
	std::vector<float> red = {0.8f,0.1f,0.1f};
	std::vector<float> green = {0.1f,0.8f,0.1f};
	for (int i {0}; i < 11; ++i)
	{
		win.createGridLine((float)i,5.f,Constants::pi / 2,color,height,width);
	}
	for (int i {1}; i < 10; ++i)
	{
		win.createGridLine(5.f,(float)i,0.f,color,height,width);
	}
	win.createGridLine(5.f,0.f,0.f,red,height,width);
	win.createGridLine(5.f,10.f,0.f,green,height,width);
	win.setGreenLinePosition(LinePosition::top);
	win.setRedLinePosition(LinePosition::bottom);
}

void createRoombas(SimWindow& win)
{
	float radius = 2.f;
	float size = 0.4f;
	std::vector<float> green = {0.15f,0.7f,0.15f};
	std::vector<float> red = {0.7f,0.15f,0.15f};
	for (int i {0}; i < 8; ++i)
	{
		float theta = i * Constants::pi / 4;
		float x = 5.f + cos(theta) * radius;
		float y = 5.f + sin(theta) * radius;
		if (i < 4)
		{
			win.createRoomba(x, y, theta, size, green);
		}
		else
		{
			win.createRoomba(x, y, theta, size, red);
		}
	}
}

void createObstacles(SimWindow& win)
{
	float radius = 3.f;
	float size = 0.4f;
	std::vector<float> pink = {0.7f,0.15f,0.7f};
	for (int i {0}; i < 4; ++i)
	{
		radius *= 1.03f;
		float theta = i * Constants::pi / 2 - Constants::pi / 4;
		float x = 5.f + cos(theta) * radius;
		float y = 5.f + sin(theta) * radius;
		win.createObstacle(x, y, theta, size, pink);
	}
}

void updateObstacleLocation(Obstacle &obstacle)
{
	/*
	float radius = sqrt(obstacle.getXpos() * obstacle.getXPos() + obstacle.getYPos() *
		obstacle.getYPos());
	float theta = obstacle.getyaw();
	obstacle.getXPos();
	*/
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
