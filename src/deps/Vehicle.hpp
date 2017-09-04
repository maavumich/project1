#ifndef _VEHICLE_HPP_
#define _VEHICLE_HPP_

#include "Entity.hpp"
#include "AnimatedEntity.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include <cstdint>
#include <vector>

/**
* @brief A class representing a vehicle in the rendered world
*/
class Vehicle : public AnimatedEntity
{
public:
	/**
	* @brief Creates a vehicle object and sets up rendering for it
	*
	* @param xInit The initial x position
	* @param yInit The initial y position
	* @param yawInit The initial yaw
	* @param radiusInit The radius
	* @param colorIn The color
	* @param program The shader program to use in drawing
	*/
	Vehicle(float xInit,
		float yInit,
		float yawInit,
		float radiusInit,
		const float* colorIn,
		Program *program);

	/**
	* @brief Updates the location and vertex data for this vehicle
	*
	* @param dt Time since the last simulation step in milliseconds
	*/
	virtual void update(unsigned dt);

	/**
	* @brief Draws this Vehicle to the rendered world
	*/
	virtual void render();
private:
	Rectangle body;
	std::vector<Rectangle> ring;
	Rectangle bar1;
	Rectangle bar2;
	Circle playerIdentifier;
	std::vector<Circle> propCaps;
	std::vector<Rectangle> props;
	int numRects = Constants::numRectsInRing;
	float thetaIncrement = 2 * PI / Constants::numRectsInRing;
	float propAngle = 0.0f;
};

#endif
