#ifndef _OBSTACLE_HPP_
#define _OBSTACLE_HPP_

#include "Entity.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include <cstdint>
#include <vector>
#include <functional>

class Obstacle : public Entity
{
	Obstacle(float xInit, float yInit, float angleInit, float radiusInit,
		unsigned int shaderProgramIdIn, float *color);
	virtual void update();
	virtual void render();
private:
	virtual void setup();
	Circle roombaBody;
	Circle pillar;
};

#endif
