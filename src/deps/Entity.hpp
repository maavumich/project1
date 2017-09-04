#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <cmath>
#include <iostream>
#include <cstdint>
#include <epoxy/gl.h>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>// glm::dot, glm::length
#include <glm/glm.hpp>
#include "Program.hpp"
#include "Constants.hpp"

constexpr static float ARENASIZEX = Constants::arenaSizeX;
constexpr static float ARENASIZEY = Constants::arenaSizeY;
constexpr static float PI = Constants::pi;

/**
* @brief The position of the goal lines (red and green lines)
*/
enum class LinePosition {top, bottom, left, right};

/**
* @brief A class representing an object in the rendered world
*/
class Entity
{
public:
	/**
	* @brief Creates an Entity and sets up rendering for that Entity
	*
	* @param xInit The initial x position
	* @param yInit The initial y position
	* @param yawInit The initial yaw
	* @param radiusInit The radius
	* @param program The shader program used to draw this Entity
	*/
	Entity(float xInit, float yInit, float yawInit, float radiusInit, Program *program);

	/**
	* @brief Sets the x and y positions of this Entity
	*
	* @param inX The x position
	* @param inY The y position
	*/
	virtual void setPosition(float inX, float inY);

	/**
	* @breif Sets the x and y position of this Entity
	*
	* @param pos_in The position as a vector (x, y)
	*/
	virtual void setPosition(glm::vec2 pos_in);

	/**
	* @brief Sets the yaw
	*
	* @param inTheta The yaw
	*/
	virtual void setYaw(float inTheta);

	/**
	* @brief Updates this Entity every simulation step. Must be implemented
	* in all derived classes
	*
	* @param dt The time since the last simulation step in milliseconds
	*/
	virtual void update(unsigned dt) = 0;

	/**
	* @brief Draws this object in the rendered world. Must be implemented in
	* all derived classes
	*/
	virtual void render() = 0;

	/**
	* @return The x position
	*/
	virtual float getXPos() const;

	/**
	* @return The y position
	*/
	virtual float getYPos() const;

	/**
	* @return The position as a vector (x, y)
	*/
	virtual glm::vec2 getPos() const;

	/**
	* @return The yaw in radians
	*/
	virtual float getYaw() const;

	/**
	* @return The radius
	*/
	virtual float getRadius() const;
protected:
	// Position, orientation, color data, as well as the shader program to use
	float x;
	float y;
	float yaw;
	float radius;
	GLuint shaderProgramId;

	static void updateTheta(float &thetaVal, float incrementVal);
};

#endif
