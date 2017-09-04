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
	Roomba(float xInit,
	       float yInit,
	       float yawInit,
	       float radiusInit,
	       const float *color,
	       Program *program);

	/**
	* @brief Updates the position and vertex data
	*
	* @param dt Time since the last simulation step in milliseconds
	*/
	virtual void update(unsigned dt);

	/**
	* @brief Draws this object in the rendered world
	*/
	virtual void render();

	/**
	* @brief Gets the color as a character. r for red, g for green, b for blue
	*
	* @return The color: red, green, or blue
	*/
	char getColor();
private:
	float color[3];
	Circle border;
	Circle roombaBody;
	Rectangle panelLarge;
	Rectangle panelSmall;
};

#endif
