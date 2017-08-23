#ifndef _VEHICLE_HPP_
#define _VEHICLE_HPP_

#include "Entity.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include <cstdint>
#include <vector>

class Vehicle : public Entity
{
public:
	Vehicle(float xInit, float yInit, float angleInit, float radiusInit,
		unsigned int shaderProgramIdIn, float *color);
	virtual void update();
	virtual void render();
private:
	virtual void setup();
	Rectangle body;
	std::vector<Rectangle> rectangles;
	std::vector<Circle> circles;
};

#endif
