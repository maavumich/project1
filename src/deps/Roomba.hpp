#ifndef _ROOMBA_HPP_
#define _ROOMBA_HPP_

#include "AnimatedEntity.hpp"
#include "Entity.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include <cstdint>
#include <vector>
#include <functional>

class Roomba : public AnimatedEntity
{
public:
	Roomba(float xInit, float yInit, float yawInit, float radiusInit,
		const float *color, Program *program);
	// Update
	virtual void update();
	// Called by renderer to render object
	virtual void render();
	// Returns 'r' for red, 'g' for green, 'b' for blue
	char getColor();
	// Returns current speed
	float getSpeed();
	// Sets the new speed
	void setSpeed(float newSpeed);
private:
	float color[3];
	Circle border;
	Circle roombaBody;
	Rectangle panelLarge;
	Rectangle panelSmall;
};

#endif
