#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <cmath>
#include <iostream>
#include <cstdint>
#include <epoxy/gl.h>
#include "Program.hpp"
#include "Constants.hpp"

enum class LinePosition {top, bottom, left, right};

constexpr float PI = 3.14159265358979f;
constexpr float ARENASIZEX = 10;
constexpr float ARENASIZEY = 10;

class Entity
{
public:
	// Constructor, creates entity, pass in all initial conditions and shader program id
	Entity(float xInit, float yInit, float yawInit, float radiusInit, Program *program);
	// Set the new position
	virtual void setPosition(float inX, float inY);
	// Set the new yaw
	virtual void setYaw(float inTheta);
	// Update the position of sub objects based on new position
	virtual void update() = 0;
	// Puts render data into openGL buffer and  renders this object
	virtual void render() = 0;
	// return current x coordinate
	virtual float getXPos() const;
	// return current y coordinate
	virtual float getYPos() const;
	// return current yaw
	virtual float getYaw() const;
	// Defines the collision radius
	virtual float getRadius() const;
protected:
	// Do opengl setup
	virtual void setup();
	// Posiition, orientation, color data, as well as the shader program to use
	float x;
	float y;
	float yaw;
	float radius;
	unsigned int shaderProgramId;
	// Constant expressions to
	constexpr static float ARENASIZEX = Constants::arenaSizeX;
	constexpr static float ARENASIZEY = Constants::arenaSizeY;
	constexpr static float PI = Constants::pi;
	static void updateTheta(float &thetaVal, float incrementVal)
	{
		thetaVal += incrementVal;
		if (thetaVal > 2.0f * 3.14159265f - 0.01f)
		{
			thetaVal = 0.0f;
		}
	}
};

#endif
