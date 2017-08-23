/**
* @file Simulator.cpp
* 
* @author Ryan Wunderly (rywunder@umich.edu)
* @date 2017-08-22
*/

#include "Simulator.hpp"

//Updates positions of objects, detects collisions, wins game,destroys obj 
void Simulator::simulate(const unsigned dt, )
{
	//update position of all objects
	//Detect a collision
	//re-update position or lose game
	//check game logic (should we score any points?) -->destroy some roombas

}

// Adds Roomba to roombaList
void Simulator::createRoomba(float xInit, float yInit, float angleInit, 
	float radiusInit, unsigned int shaderProgramIdIn, float *color,
	std::function <void(Roomba&)> func = [](Roomba&){})
{
	roombaList.emplace_back(xInit, yInit, angleInit, radiusInit, 
		shaderProgramIdIn, color, func);
}

// Adds Obstacle to obstacleList
void Simulator::createObstacle(float xInit, float yInit, float angleInit, 
	float radiusInit, unsigned int shaderProgramIdIn, float *color,
	std::function <void(Obstacle&)> func = [](Obstacle&){})
{
	obstacleList.emplace_back(xInit, yInit, angleInit, radiusInit, 
	 shaderProgramIdIn, color, func);
}

void Simulator::createVehicle()
{
	vehicle = Vehicle();
}

const std::vector<Roomba>& Simulator::getRoombaList()
{
	return roombaList;
}

const std::vector<Obstacle>& Simulator::getObstacleList()
{
	return obstacleList;
}

const Vehicle& Simulator::getVehicle()
{
	return vehicle;
}
