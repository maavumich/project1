/**
* @file Simulator.cpp
* 
* @author Ryan Wunderly (rywunder@umich.edu)
* @date 2017-08-22
*/
#include <glm/vec2.hpp>// glm::vec2
#include <glm/geometric.hpp>// glm::dot, glm::normalize
#include <cassert>
#include <iostream>

#include "Simulator.hpp"

using std::vector;
using std::queue;
using std::atan2;
using std::cos;
using std::sin;

using glm::normalize;
using glm::dot;
using glm::vec2;


//Updates positions of objects, detects collisions, wins game,destroys obj 
//Called at 16.7 ms
bool Simulator::simulate(const unsigned dt)
{
	//Apply Action which updates position of vehicle
	if(!actionQueue.empty())
	{
		actionQueue.front()(vehicle);
		actionQueue.pop_front();
	}

	//Update position of all objects
	for(auto obstacle: obstacleList)
	{
		updateObstacleLocation(obstacle);
	}

	for(auto roomba: roombaList)
	{
		updateRoombaLocation(roomba);
	}

	// Check for any collisions and update the positions until no overlapping 
	// occurs
	bool collisionOccurred = true;

	while(collisionOccurred)
	{
		collisionOccurred = false; //First assume no collsions

		// Comparisons with roombas to check for collisions

		for(auto it = roombaList.begin(), auto end = roombaList.end(); 
			it != end; ++it)
		{
			// Compare all roombas to eachother
			for(auto it2 = it + 1; it2 != end; ++it2)
			{
				if(isCollision(*it, *it2))
				{
					collisionOccurred = true;
					physicsCollision(*it, *it2);
				}
			}

			// Compare each roomba to each obstacle
			for(auto itO = obstacleList.begin(), auto endO = obstacleList.end(); 
				itO != endO; ++itO)
			{
				if(isCollision(*it, *itO))
				{
					collisionOccurred = true;
					physicsCollision(*it, *itO);
				}
			}

			//Compare each roomba to the vehicle
			if(isCollision(*it, vehicle))
			{
				collisionOccurred = true;
				physicsCollision(*it, vehicle);
			}
		}

		// Comparisons with obstacles
		for(auto it = obstacleList.begin(), auto end = obstacleList.end(); 
			it != end; ++it)
		{
			// Compare all obstacles to eachother
			for(auto it2 = it + 1; it2 != end; ++it2)
			{
				if(isCollision(*it, *it2))
				{
					collisionOccurred = true;
					physicsCollision(*it, *it2);
				}
			}

			//Compare each obstacle to the vehicle
			if(isCollision(*it, vehicle))
			{
				collisionOccurred = true;
				//physicsCollision(*it, vehicle);

				// We have lost the game!
				gameResults = false; //
				cout << "Collsion with an obstacle! You LOSE\n";

				return true; // return that the game ended
			}
		}
	}


	//check game logic (should we score any points?)-->destroy some roombas

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
bool Simulator::isCollision(const AnimatedEntity& aEnt1, 
	const AnimatedEntity& aEnt2)
{
	// Get the positions of both objects
	vec2 aEnt1Pos(aEnt1.getXPos(), aEnt1.getYPos()); 
	vec2 aEnt2Pos(aEnt2.getXPos(), aEnt2.getYPos());

	//Get the distance between the objects
	double dist = normalize(aEnt1Pos - aEnt2Pos);

	//Check to see if radius between entities 
	if(dist < (aEnt1.getRadius() +  aEnt2.getRadius()))
	{
		return true;
	}

	return false;
}

// Implement physics for a collision between entities
// Effects updates positions, yaw, and speed of the entities in collision
void Simulator::physicsCollision(AnimatedEntity& aEnt1, AnimatedEntity& aEnt2, 
	const unsigned dt)
{
	int mass1 = aEnt1.getMass(), mass2 = aEnt2.getMass();

	// Get the positions of both objects
	vec2 aEnt1Pos(aEnt1.getXPos(), aEnt1.getYPos()); 
	vec2 aEnt2Pos(aEnt2.getXPos(), aEnt2.getYPos());

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

	// Set new positions of both objects to right before collision (overlap)
	vec2 aEnt1FPos = aEnt1Pos; 
	vec2 aEnt2FPos = aEnt2Pos;
	double timestep = dt / 10.0;

	// Go back in time until there is no collision between objects 
	while(isCollision(aEnt1, aEnt2))
	{
		aEnt1FPos = -1 * vi1 * timestep + aEnt1Pos;
		aEnt2FPos = -1 * vi2 * timestep + aEnt2Pos;

		//Set the new positions then check for the collision
		aEnt1.setPosition(aEnt1FPos[0], aEnt1FPos[1]);
		aEnt2.setPosition(aEnt2FPos[0], aEnt2FPos[1]);
	}

	// Set the new speed and yaw of the objects
	aEnt1.setSpeed(normalize(v1final));
	aEnt1.setYaw(atan2(v1final[1], v1final[0]));
	aEnt2.setSpeed(normalize(v2final));
	aEnt2.setYaw(atan2(v2final[1], v2final[0]));
}