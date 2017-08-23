/**
* @file Simulator.hpp
* 
* @author Ryan Wunderly (rywunder@umich.edu)
* @date 2017-08-22
*/

#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <vector>
#include "Vehicle.hpp"
#include "Roomba.hpp"
#include "Obstacle.hpp"


class Simulator
{
public:

	//Updates positions of objects, detects collisions, wins game 
	void simulate(const unsigned dt);

	// Adds Roomba to roombaList
	void createRoomba(float xInit, float yInit, float angleInit, float radiusInit,
		unsigned int shaderProgramIdIn, float *color,
		std::function <void(Roomba&)> func = [](Roomba&){});

	// Adds Obstacle to obstacleList
	void createObstacle(float xInit, float yInit, float angleInit, float radiusInit,
		unsigned int shaderProgramIdIn, float *color,
		std::function <void(Obstacle&)> func = [](Obstacle&){});

	// Creates and intializes the vehicle on the environment
	void createVehicle();

	// Returns the vector of Roombas
	const std::vector<Roomba>& getRoombaList();

	// Returns the vector of Obstacles
	const std::vector<Obstacle>& getObstacleList();

	// Returns the vector of Vehicles
	const Vehicle& getVehicle();

	// Updates the location of roomba
	std::function<void(Roomba&)> updateRoombaLocation;

	// Updates the location of the obstacle
	std::function<void(Obstacle&)> updateObstacleLocation;

private:

	// Objects in the environment
	std::vector<Roomba> roombaList;
	std::vector<Obstacle> obstacleList; 
	Vehicle vehicle;

	LinePosition redLinePosition;
	LinePosition greenLinePosition;

	int sizeEnvironment = 10; // Default 10X10 m
};

#endif
