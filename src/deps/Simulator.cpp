/**
* @file Simulator.cpp
* 
* @author Ryan Wunderly (rywunder@umich.edu)
* @date 2017-08-22
*/
#include <glm/vec2.hpp>// glm::vec2
#include <glm/geometric.hpp>// glm::dot, glm::normalize
#include <cassert>
#include "Simulator.hpp"

using std::vector;
using std::queue;
using glm::normalize;
using glm::dot;
using glm::vec2;
using glm::sin;
using glm::cos;
using glm::atan;

//Updates positions of objects, detects collisions, wins game,destroys obj 
void Simulator::simulate(const unsigned dt)
{
	//update position of all objects
	for(auto obstacle: obstacleList)
	{
		updateObstacleLocation(obstacle);
	}

	for(auto roomba: roombaList)
	{
		updateRoombaLocation(roomba);
	}

	//Check for any collisions

	
	//re-update position or lose game
	//check game logic (should we score any points?) -->destroy some roombas

}

// Adds Roomba to roombaList
void Simulator::createRoomba(float xInit, float yInit, float angleInit, 
	float radiusInit, unsigned int shaderProgramIdIn, float *color,
	std::function <void(Roomba&)> func = [](Roomba&){})
{
	roombaList.emplace_back(xInit, yInit, angleInit, radiusInit, 
		shaderProgramIdIn, color);

	updateRoombaLocation = func; // sets the path for roombas
}

// Adds Obstacle to obstacleList
void Simulator::createObstacle(float xInit, float yInit, float angleInit, 
	float radiusInit, unsigned int shaderProgramIdIn, float *color,
	std::function <void(Obstacle&)> func = [](Obstacle&){})
{
	obstacleList.emplace_back(xInit, yInit, angleInit, radiusInit, 
	 shaderProgramIdIn, color);

	updateObstacleLocation = func; // sets the path for obstacles
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

// Get score to update text
int Simulator::getScore()
{
	return score;
}
bool Simulator::getGameResults()
{
	return gameResults;
}

void Simulator::addAction(std::function <void(Vehicle&)> action)
{
	actionQueue.push_back(action);
}

// Checks if two objects are colliding
bool Simulator::isCollision(const AnimatedEntity& aEnt1, const AnimatedEntity& aEnt2)
{
	assert(false);
}

//Objects collided so what happens to them?
//Effects updates positions of the animated entities
Simulator::physicsCollision(AnimatedEntity& aEnt1, AnimatedEntity& aEnt2, 
	const unsigned dt)
{
	int mass1 = aEnt1.getMass(), mass2 = aEnt2.getMass();

	// Get the positions of both objects
	vec2 aEnt1Pos(aEnt1.getXPos, aEnt1.getYPos()); 
	vec2 aEnt2Pos(aEnt2.getXPos, aEnt2.getYPos());

	// Unit normal vector and unit tangent vector to the objects
	vec2 unormal = (aEnt1Pos - aEnt2Pos) / normalize((aEnt1Pos - aEnt2Pos));
	vec2 utangent(-1 * unormal[1], unormal[0]);

	// Initial velocity vectors
	vec2 vi1(aEnt1.getSpeed()*sin(aEnt1.getYaw()), 
		aEnt1.getSpeed()*cos(aEnt1.getYaw()));

	vec2 vi2(aEnt2.getSpeed()*sin(aEnt2.getYaw()), 
		aEnt2.getSpeed()*cos(aEnt2.getYaw()));

	// Normal and tangential scalar velocities
	double s1norm = dot(unormal, vi1);
	double s1tan  = dot(unormal, vi1);
	double s2norm = dot(unormal, vi2);
	double s2tan  = dot(unormal, vi2); 

	// Note: The tangential velocities are not affected by collision
	// Calculate the normal scalar velocities after the collsion
	double s1fnorm = s1norm * (mass1 - mass2) + (2 * mass2 * s2norm) / 
		(mass1 + mass2);
	double s2fnorm = s2norm * (mass2 - mass1) + (2 * mass1 * s1norm) / 
		(mass1 + mass2);

	// Convert the scalar velocities into vectors
	vec2 vf1norm = s1fnorm * unormal; 
	vec2 vf1tan = s1tan * utangent;
	vec2 vf2norm = s2fnorm * unormal;
	vec2 vf2tan = s2tan * utangent;

	// Find final velocity vectors for each object
	vec2 v1final = vf1norm + vf1tan;
	vec2 v2final = vf2norm + vf2tan;

	// set new positions of both objects to right before collision (overlap)
	vec2 aEnt1FPos = aEnt1Pos; 
	vec2 aEnt2FPos = aEnt2Pos;
	double timestep = dt / 10.0;

	// Go back in time until there is no collision between objects 
	while(isCollision(aEnt1, aEnt2))
	{
		aEnt1FPos = -1 * vi1 * timestep + aEnt1Pos}

}