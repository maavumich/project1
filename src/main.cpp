#include "deps/SimWindow.hpp"
#include "deps/Constants.hpp"
#include <thread>

// These are hire to help you.
using namespace std;
using std::cos;
using std::sin;
using glm::vec2;
auto TOP = LinePosition::top;
auto BOTTOM = LinePosition::bottom;
auto LEFT = LinePosition::left;
auto RIGHT = LinePosition::right;


/**
 * Function prototypes. These let the main function know that these functions exist. They are
 * defined below along with a breif description of what they should do.
 */
void updateRoombaLocation(Roomba& roomba);
void updateObstacleLocation(Obstacle& obstacle);
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
void createGridLines(SimWindow& win);
void createRoombas(SimWindow& win);
void createObstacles(SimWindow& win);


int main(int argc, char** argv)
{
	auto app = Gtk::Application::create(argc, argv, "org.maav.training.simulation");
	// Create the sim window object
	SimWindow win{};

	// Attach event handlers here
	win.setRoombaUpdateFunc(updateRoombaLocation);
	// Set up the arena
	createGridLines(win);
	createRoombas(win);
	createObstacles(win);
	win.setObstacleUpdateFunc(updateObstacleLocation);

	// Attach Key Bindings
	win.attachEventHandler(GDK_KEY_w, vehicleMoveForward);
	win.attachEventHandler(GDK_KEY_s, vehicleMoveBackward);
	win.attachEventHandler(GDK_KEY_a, vehicleMoveLeftward);
	win.attachEventHandler(GDK_KEY_d, vehicleMoveRightward);
	// Stop vehicle movement when key is released
	win.attachEventStopHandler(GDK_KEY_w, vehicleStopMoveForward);
	win.attachEventStopHandler(GDK_KEY_s, vehicleStopMoveBackward);
	win.attachEventStopHandler(GDK_KEY_a, vehicleStopMoveLeftward);
	win.attachEventStopHandler(GDK_KEY_d, vehicleStopMoveRightward);
	// Attach any other key bindings you want here (before the return statement)

	return app->run(win);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// You must implement the following functions. Below this section are functions which have already
// been implemented for you. You may look at them for "inspiration" if you get stuck
// The starter code can be compiled successfully, though nothing will remain on screen for more than
// a fraction of a second until you place at least one roomba. You can exit the simulation at any
// time by pressing the escape "Esc" key on your keyboard
///////////////////////////////////////////////////////////////////////////////////////////////////


/**
* REQUIRES: win is a valid SimWindow
*
* EFFECTS: Draws grid lines. The lines should appear at every meter on the field. It should look
* like graph paper if done correctly. Also sets the green and red line positions on the field.
*
* MODIFIER: The field in the simulation
*/
void createGridLines(SimWindow& win)
{
	// Write code to place grid lines in field here. USE LOOPS!
}

/**
* REQUIRES: win is a valid SimWindow
*
* EFFECTS: Places 8 to 10 Roombas in a circle about the center of the field. The roombas must be
* half red and half green. Roombas of like color must be next to each other.
*
* MODIFIES: The field in the simulation
*/

void createRoombas(SimWindow& win)
{
	// Write code to place roombas on the field here
}

/**
* REQUIRES: vehicle is a valid Vehicle
*
* EFFECTS: Causes the vehicle to move forward
*
* MODIFIES: The vehicle
*/

void vehicleMoveForward(Vehicle& vehicle)
{
	// Implement this
}

/**
* REQUIRES: vehicle is a valid Vehicle
*
* EFFECTS: Causes the vehicle to move backward
*
* MODIFIES: The vehicle
*/
void vehicleMoveBackward(Vehicle& vehicle)
{
	// Implement this
}

/**
* REQUIRES: vehicle is a valid Vehicle
*
* EFFECTS: Causes the vehicle to move left
*
* MODIFIES: The vehicle
*/
void vehicleMoveLeftward(Vehicle& vehicle)
{
	// Implement this
}

/**
* REQUIRES: vehicle is a valid Vehicle
*
* EFFECTS: Causes the vehicle to move right
*
* MODIFIES: The vehicle
*/
void vehicleMoveRightward(Vehicle& vehicle)
{
	// Implement this
}

/**
* REQUIRES: vehicle is a valid Vehicle
*
* EFFECTS: Causes the vehicle to stop moving forward
*
* MODIFIES: The vehicle
*/
void vehicleStopMoveForward(Vehicle& vehicle)
{
	// Implement this
}

/**
* REQUIRES: vehicle is a valid Vehicle
*
* EFFECTS: Causes the vehicle to stop moving backward
*
* MODIFIES: The vehicle
*/
void vehicleStopMoveBackward(Vehicle& vehicle)
{
	// Implement this
}

/**
* REQUIRES: vehicle is a valid Vehicle
*
* EFFECTS: Causes the vehicle to stop moving left
*
* MODIFIES: The vehicle
*/
void vehicleStopMoveLeftward(Vehicle& vehicle)
{
	// Implement this
}

/**
* REQUIRES: vehicle is a valid Vehicle
*
* EFFECTS: Causes the vehicle to stop moving right
*
* MODIFIES: The vehicle
*/
void vehicleStopMoveRightward(Vehicle& vehicle)
{
	// Implement this
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// The following functions have been implemented for you. You may use them for "inspiration"
///////////////////////////////////////////////////////////////////////////////////////////////////


/**
* REQUIRES: win is a valid SimWindow
*
* EFFECTS: Places 4 obstacles in the arena in a square about the center of the field.
*
* MODIFIER: The field in the simulation
*/
void createObstacles(SimWindow& win)
{
	float radius = 3.f;
	float size = 0.4f;
	std::vector<float> pink = {0.7f,0.15f,0.7f};
	for (int i {0}; i < 4; ++i)
	{
		radius *= 1.03f;
		float theta = i * PI / 2 - PI / 4;
		float x = 5.f + cos(theta) * radius;
		float y = 5.f + sin(theta) * radius;
		win.createObstacle(x, y, theta, size, pink);
	}
}

/**
* REQUIRES: obstacle is a valid obstacle (Assume this condition is satisfied)
*
* EFFECTS: Moves the roombas in a circle around the center
*
* MODIFIES: The velocity of the Obstacle
*/
void updateObstacleLocation(Obstacle &obstacle)
{
	float theta = obstacle.getTheta();
	vec2 newVel{-sin(theta),
		    cos(theta)};
	obstacle.setVelocity(newVel);
}

/**
* REQUIRES: roomba is a valid Roomba
*
* EFFECTS: Updates the roomba's state. By default this just makes the roomba rotate in place.
*
* MODIFIES: The Roomba
*/
void updateRoombaLocation(Roomba& roomba)
{
	roomba.setYaw(roomba.getYaw() + Constants::pi / 180);
}

