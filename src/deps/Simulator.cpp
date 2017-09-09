#include "Simulator.hpp"
#include <glm/vec2.hpp>// glm::vec2
#include <glm/geometric.hpp>// glm::dot, glm::length
#include <cassert>
#include <iostream>
#include <algorithm>


using std::vector;
using std::queue;
using std::atan2;
using std::cos;
using std::sin;

using glm::length;
using glm::dot;
using glm::vec2;
using std::cout;

Simulator::Simulator() : redLinePosition{LinePosition::bottom},
			 greenLinePosition{LinePosition::top}
{

}

//Updates positions of objects, detects collisions, wins game,destroys obj
//Called at 16.7 ms
bool Simulator::simulate(const unsigned dt)
{
	//Update position of all objects
	for(auto& obstacle: obstacleList)
	{
		updateObstacleLocation(obstacle);
	}

	for(auto& roomba: roombaList)
	{
		updateRoombaLocation(roomba);
	}

	// Remove roombas in goal
	for(auto it = roombaList.begin(), end = roombaList.end(); it != end; ++it) {
		int status = roombaInGoal(&*it);
		if(status) {
			roombaList.erase(it);
			switch(status){
				case 1 : score += 69; break;
				case 2 : score -= 42; break;
			}
		}
	}

	// resolve vehicle collisions
	for(auto& v : vehicles) {
		handleWallCollision(&v);
		for(auto& vv : vehicles) {
			if(&vv != &v && detectCollision(&v, &vv)) {
				resolveCollision(&v, &vv);
			}
		}
		for(auto& r : roombaList) {
			if(detectCollision(&v, &r)) {
				resolveCollision(&v, &r);
			}
		}
		for(auto& o : obstacleList) {
			if(detectCollision(&v, &o)) {
				return true; // Game ends on collision with obstacle
				//resolveCollision(&v, &o);
			}
		}
	}

	for(auto& r : roombaList) {
		handleWallCollision(&r);
		for(auto& rr : roombaList) {
			if(&rr != &r && detectCollision(&r, &rr)) {
				resolveCollision(&r, &rr);
			}
		}
		for(auto& o : obstacleList) {
			if(detectCollision(&r, &o)) {
				resolveCollision(&r, &o);
			}
		}
	}

	for(auto& o : obstacleList) {
		handleWallCollision(&o);
		for(auto& oo : obstacleList) {
			if(&oo != &o && detectCollision(&o, &oo)) {
				resolveCollision(&o, &oo);
			}
		}
	}

	//The game has ended
	if(roombaList.empty())
	{
		return true; // return that the game ended
	}

	for(auto& v : vehicles) {
		v.update(dt);
	}

	for(auto& r : roombaList) {
		r.update(dt);
	}

	for(auto& o : obstacleList) {
		o.update(dt);
	}

	return false; //The game should continue

}

// Adds Roomba to roombaList
void Simulator::createRoomba(float xInit, float yInit, float angleInit,
	float radiusInit, Program* shaderProgramIdIn, float *color)
{
	roombaList.emplace_back(xInit, yInit, angleInit, radiusInit, color,
		shaderProgramIdIn);
}

// Adds Obstacle to obstacleList
void Simulator::createObstacle(float xInit, float yInit, float angleInit,
	float radiusInit, Program* shaderProgramIdIn, float *color)
{
	obstacleList.emplace_back(xInit, yInit, angleInit, radiusInit, color,
	 shaderProgramIdIn);
}

void Simulator::setRoombaUpdateFunc(std::function<void(Roomba&)> func)
{
	updateRoombaLocation = func;
}

void Simulator::setObstacleUpdateFunc(std::function<void(Obstacle&)> func)
{
	updateObstacleLocation = func;
}

void Simulator::createVehicle(Program* prog)
{
	if (vehicles.size() == 0){
		vehicles.emplace_back(0.f, 0.f, PI / 4.f, 1.f, Constants::playerOneColor, prog);
	} else if (vehicles.size() == 1) {
		std::cerr << "Make sure you know what you're doing with 2 Vehicles!\n";
		vehicles.emplace_back(10.f, 10.f, PI / 4.f, 1.f, Constants::playerTwoColor, prog);
	} else {
		std::cerr << "Why are you making more than two vehicles????\n";
	}
}

std::vector<Roomba>& Simulator::getRoombaList()
{
	return roombaList;
}

std::vector<Obstacle>& Simulator::getObstacleList()
{
	return obstacleList;
}

std::vector<Vehicle>& Simulator::getVehicle()
{
	return vehicles;
}

// Get score to update text
int Simulator::getScore()
{
	return score;
}

// Return 0: not in goal, 1: in goal, 2: in incorrect goal
int Simulator::roombaInGoal(const Roomba* const roomba)
{
	switch(greenLinePosition)
	{
		case LinePosition::top :
			if(roomba->getYPos() > sizeEnvironment)
				return 1;
			break;
		case LinePosition::bottom :
			if(roomba->getYPos() < 0)
				return 1;
			break;
		case LinePosition::left :
			if(roomba->getXPos() < 0)
				return 1;
			break;
		case LinePosition::right :
			if(roomba->getXPos() > sizeEnvironment)
				return 1;
			break;
	}

	switch(redLinePosition)
	{
		case LinePosition::top :
			if(roomba->getYPos() > sizeEnvironment)
				return 2;
			break;
		case LinePosition::bottom :
			if(roomba->getYPos() < 0)
				return 2;
			break;
		case LinePosition::left :
			if(roomba->getXPos() < 0)
				return 2;
			break;
		case LinePosition::right :
			if(roomba->getXPos() > sizeEnvironment)
				return 2;
			break;
	}

	return 0;
}

bool Simulator::detectCollision(const AnimatedEntity* const a, const AnimatedEntity* const b)
{
	float r = a->getRadius() + b->getRadius();
	float dist = length(b->getPos() - a->getPos());
	return r > dist;
}

void Simulator::resolveCollision(AnimatedEntity* a, AnimatedEntity* b)
{
	vec2 rv = b->getVelocitySum() - a->getVelocitySum();
	vec2 normal = b->getPos() - a->getPos();
	normal /= length(normal);
	float nvel = dot(rv, normal);
	if(nvel > 0) return; // don't resolve if objects moving away from each other

	float penetration = length(b->getPos() - a->getPos()) - (a->getRadius() + b->getRadius());
	penetration = penetration < 0 ? -1 * penetration : 0;
	float emin = glm::min(a->getRestitution(), b->getRestitution());
	float j = -1.f * (1.f + emin) * nvel;
	j /= 1.f/a->getMass() + 1.f/b->getMass();
	vec2 impulse = j * normal;
	vec2 avel =  a->getVelocitySum() - (1.f / a->getMass()) * impulse;
	vec2 bvel =  b->getVelocitySum() + (1.f / b->getMass()) * impulse;
	a->setCollisionVel((1 + penetration) * (avel - a->getVelocity()));
	b->setCollisionVel((1 + penetration) * (bvel - b->getVelocity()));

	if(penetration > 0.035) {
		a->setPosition(a->getPos() - penetration * normal);
	}

}

void Simulator::handleWallCollision(Roomba* a)
{
	vec2 pos = a->getPos();
	vec2 vel = a->getVelocitySum();
	vec2 cvel;
	float r = a->getRadius();
	float ledge = pos[0] - r, redge = pos[0] + r, tedge = pos[1] + r, bedge = pos[1] - r;
	bool collision = false;
	if(ledge < 0.f && !isGoalLine(LinePosition::left)) {
		cvel = {1.f, vel[1]};
		collision = true;
	} else if (redge > Constants::arenaSizeX && !isGoalLine(LinePosition::right)) {
		cvel = {-1.f, vel[1]};
		collision = true;
	}

	if(bedge < 0.f && !isGoalLine(LinePosition::bottom)) {
		cvel = {vel[0], 1.f};
		collision = true;
	} else if (tedge > Constants::arenaSizeY && !isGoalLine(LinePosition::top)) {
		cvel = {vel[0], -1.f};
		collision = true;
	}

	if(collision){
		a->setCollisionVel(cvel);
	}
}

void Simulator::handleWallCollision(Obstacle* a)
{
	vec2 pos = a->getPos();
	vec2 vel = a->getVelocitySum();
	vec2 cvel;
	float r = a->getRadius();
	float ledge = pos[0] - r, redge = pos[0] + r, tedge = pos[1] + r, bedge = pos[1] - r;
	bool collision = false;
	if(ledge < 0.f) {
		cvel = {1.f, vel[1]};
		collision = true;
	} else if (redge > Constants::arenaSizeX) {
		cvel = {-1.f, vel[1]};
		collision = true;
	}

	if(bedge < 0.f) {
		cvel = {vel[0], 1.f};
		collision = true;
	} else if (tedge > Constants::arenaSizeY) {
		cvel = {vel[0], -1.f};
		collision = true;
	}

	if(collision){
		a->setCollisionVel(cvel);
	}
}

void Simulator::handleWallCollision(Vehicle* a)
{
	// Do something unique here or pass off to Animated Entity handler
	(void)a;
}

bool Simulator::isGoalLine(LinePosition pos)
{
	return pos == greenLinePosition || pos == redLinePosition;
}
