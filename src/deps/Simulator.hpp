/**
* @file Simulator.hpp
*
* @author Ryan Wunderly (rywunder@umich.edu), Romario Pashollari (rpash@umich.edu)
* @date 2017-08-22
*/

#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <vector>
#include <queue>

#include "Vehicle.hpp"

#include "Roomba.hpp"
#include "Obstacle.hpp"
#include "Constants.hpp"


/**
* @brief A class representing the simulated world
*/
class Simulator
{
public:
	/**
	* @brief Constructs an empty simulator
	*/
	Simulator();

	/**
	* @brief Executes a simulation step
	*
	* @detailed Updates the position of all objects based on a preset update function. Detects
	* collisions between objets in the simulation and the field borders and resolves any such
	* collisions. Calculates the game score based on how many Roombas left on the right side of
	* the arena. Will always return false unless the simulation has to end.
	*
	* @param dt Time since the last simulation step in milliseconds
	*
	* @return Whether the simulation should continue
	*/
	bool simulate(const unsigned dt);

	/**
	* @brief Creates a Roomba in the rendered world
	*
	* @param xInit The intial x position
	* @param yInit The intial y position
	* @param angleInit The initial yaw
	* @param radiusInit The radius
	* @param shaderProgramIdIn The shader program to use in rendering
	* @param color The color of this Roomba
	*/
	void createRoomba(float xInit, float yInit, float angleInit, float radiusInit,
		Program* shaderProgramIdIn, float *color);

	/**
	* @brief Creates a Obstacle in the rendered world
	*
	* @param xInit The intial x position
	* @param yInit The intial y position
	* @param angleInit The initial yaw
	* @param radiusInit The radius
	* @param shaderProgramIdIn The shader program to use in rendering
	* @param color The color of this Obstacle
	*/
	void createObstacle(float xInit, float yInit, float angleInit, float radiusInit,
		Program* shaderProgramIdIn, float *color);

	/**
	* @brief Sets the function to be called that updates the Roombas each simulation step
	*
	* @param func The function to call each simulation step
	*/
	void setRoombaUpdateFunc(std::function<void(Roomba&)> func);

	/**
	* @brief Sets the function to be called that updates the Obstacles each simulation step
	*
	* @param func The function to call each simulation step
	*/
	void setObstacleUpdateFunc(std::function<void(Obstacle&)> func);

	/**
	* @brief Creates a Vehicle in the field. A max of two Vehicles can be created
	*
	* @param prog The shader program to use in rendering the vehicle
	*/
	void createVehicle(Program* prog);

	/**
	* @return A vector of Roombas in the Simulator
	*/
	std::vector<Roomba>& getRoombaList();

	/**
	* @return A vector of Obstacles in the Simulator
	*/
	std::vector<Obstacle>& getObstacleList();

	/**
	* @return A vector of Vehicles in the Simulator
	*/
	std::vector<Vehicle>& getVehicle();

	/**
	* @return The points scored this game
	*/
	int getScore();

	/**
	* @brief Sets the position of the green score line
	*
	* @param newPos The position of the line
	*/
	void setGreenLinePosition(LinePosition newPos)
	{
		greenLinePosition = newPos;
	}

	/**
	* @brief Sets the position of the red score line
	*
	* @param newPos The position of the line
	*/
	void setRedLinePosition(LinePosition newPos)
	{
		redLinePosition = newPos;
	}


private:
	// Return 0: not in goal, 1: in goal, 2: in incorrect goal
	/**
	* @brief Finds out whether the roomba is considered past a goal line
	*
	* @param roomba The roomba to check
	*
	* @return 0 if not in goal, 1 if in correct goal, 2 if in incorrect goal
	*/
	int roombaInGoal(const Roomba* const roomba);

	/**
	* @brief Checks whether a particular position is a goal line
	*
	* @param pos The position to check
	*
	* @return Whether the position is a goal line
	*/
	bool isGoalLine(LinePosition pos);

	/**
	* @brief Detects Circle v Cricle collisions
	*
	* @param a An AnimatedEntity to check
	* @param b An AnimatedEntity to check
	*
	* @return Whether the two AnimatedEntities collide
	*/
	bool detectCollision(const AnimatedEntity* const a, const AnimatedEntity* const b);

	/**
	* @brief Performs impulse resolution on detected collisions
	*
	* @param a An AnimatedEntity to perform collision resolution on
	* @param b An AnimatedEntity to perform collision resolution on
	*/
	void resolveCollision(AnimatedEntity* a, AnimatedEntity* b);

	/**
	* @brief Handles Roomba v Wall collisions
	*
	* @param a The Roomba to handle
	*/
	void handleWallCollision(Roomba* a);

	/**
	* @brief Handles Obstacle v Wall collisions
	*
	* @param a The Obstacle to handle
	*/
	void handleWallCollision(Obstacle* a);

	/**
	* @brief Handles Vehicle v Wall collisions
	*
	* @param a The Vehicle to handle
	*/
	void handleWallCollision(Vehicle* a);

	// Update functions for Roombas and Obstacles
	std::function <void(Roomba&)> updateRoombaLocation;
	std::function<void(Obstacle&)> updateObstacleLocation;

	// Objects in the environment
	std::vector<Roomba> roombaList;
	std::vector<Obstacle> obstacleList;
	std::vector<Vehicle> vehicles;

	// Positions of goal lines
	LinePosition redLinePosition = LinePosition::left;
	LinePosition greenLinePosition = LinePosition::right;

	int sizeEnvironment{10}; // Default 10X10m
	int score{0};
};

#endif
