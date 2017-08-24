#ifndef _OBSTACLE_HPP_
#define _OBSTACLE_HPP_

#include "AnimatedEntity.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include <cstdint>
#include <vector>
#include <functional>

class Obstacle : public AnimatedEntity
{
public:
	Obstacle(float xInit, float yInit, float angleInit, float radiusInit,
		Program *program, float *color);
	virtual void update();
	virtual void render();
private:
	virtual void setup();
	Circle roombaBody;
	Circle pillar;
};

#endif
