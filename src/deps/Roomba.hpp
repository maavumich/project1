#ifndef _ROOMBA_HPP_
#define _ROOMBA_HPP_

#include "Entity.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include <cstdint>
#include <vector>
#include <functional>

class Roomba : public Entity
{
public:
	Roomba(float xInit, float yInit, float angleInit, float radiusInit,
		unsigned int shaderProgramIdIn, float *color,
		std::function <void(Roomba&)> func = [](Roomba&){});
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
	// Called before render() by render to do pre render setup
	virtual void setup();
	float speed {0};
	Circle roombaBody;
	Rectangle panelLarge;
	Rectangle panelSmall;
};

#endif
