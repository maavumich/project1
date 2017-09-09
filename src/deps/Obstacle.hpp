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
	/**
	* @brief Constructs an Obstacle and sets up rendering
	*
	* @param xInit The initial x position
	* @param yInit The initial y position
	* @param yawInit The initial yaw
	* @param radiusInit The radius
	* @param colorIn The color in RGB [0, 1]
	* @param program The shader program to use in drawing
	*/
	Obstacle(float xInit,
		 float yInit,
		 float yawInit,
		 float radiusInit,
		 const float *colorIn,
		 Program *program);

	/**
	* @brief Draws this object in the rendered world
	*/
	virtual void render();

	/**
	* @brief Updates the location and vertex data
	*
	* @param dt Time since the last simulation step in milliseconds
	*/
	virtual void update(unsigned dt);

	float getTheta() const;

private:
	Circle border;
	Circle roombaBody;
	Circle pillar;
	Circle outerBorder;
	Circle innerBorder;
	Circle insidePillar;
	float theta;
};

#endif
