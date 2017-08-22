#ifndef _OBSTACLE_HPP_
#define _OBSTACLE_HPP_

#include "Entity.hpp"
#include "AnimatedEntity.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include <cstdint>
#include <vector>
#include <functional>

class Obstacle : public AnimatedEntity
{
public:
	Obstacle(float xInit, float yInit, float yawInit, float radiusInit,
		const float *colorIn, Program *program);
	virtual void update();
	virtual void render();
	float getSpeed();
	void setSpeed(float newSpeed);
private:
	Circle border;
	Circle roombaBody;
	Circle pillar;
	Circle outerBorder;
	Circle innerBorder;
	Circle insidePillar;
};

#endif
