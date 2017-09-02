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
	/**
	* @brief Creates Roomba to render
	*
	* @param xInit Initial x position
	* @param yInit Initial y position
	* @param yawInit Initial yaw
	* @param radiusInit Radius of roomba
	* @param color Colot of plate
	* @param program The shader program to use in drawing this Roomba
	*/
	Roomba(float xInit, float yInit, float yawInit, float radiusInit,
		const float *color, Program *program);

	// Update
	virtual void update(unsigned dt);
	// Called by renderer to render object
	virtual void render();
	// Returns 'r' for red, 'g' for green, 'b' for blue
	char getColor();
	// Returns current speed
	float getSpeed();
	// Sets the new speed
	void setSpeed(float newSpeed);
	// Updates the location of this object
	std::function<void(Roomba&)> updateLocation;
private:
	float color[3];
	Circle border;
	Circle roombaBody;
	Rectangle panelLarge;
	Rectangle panelSmall;
};

#endif
