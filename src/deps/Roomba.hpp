#ifndef _ROOMBA_HPP_
#define _ROOMBA_HPP_

#include "AnimatedEntity.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include <cstdint>
#include <vector>
#include <functional>

class Roomba : public AnimatedEntity
{
public:
	Roomba(float xInit, float yInit, float angleInit, float radiusInit,
		unsigned int shaderProgramIdIn, float *color);
	// Update
	virtual void update();
	// Called by renderer to render object
	virtual void render();
	// Returns 'r' for red, 'g' for green, 'b' for blue
	char getColor();
private:
	// Called before render() by render to do pre render setup
	virtual void setup();
	Circle roombaBody;
	Rectangle panelLarge;
	Rectangle panelSmall;
};

#endif
