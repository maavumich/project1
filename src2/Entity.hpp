#include <cmath>
#include <iostream>
#include <cstdint>
#include <epoxy/gl.h>

class Entity
{
public:
	Entity(float xInit, float yInit, float angleInit, float radiusInit,
		unsigned int shaderProgramIdIn, float arenaSizeXIn,
		float arenaSizeYIn);
	virtual void setPosition(float inX, float inY);
	virtual void setAngle(float inTheta);
	virtual void update();
	virtual void setup();
	virtual void render();
	virtual float getXPos();
	virtual float getYPos();
	virtual float getAngle();
	virtual float getRadius();
protected:
	// Posiition, orientation, color data, as well as the shader program to use
	float x;
	float y;
	float angle;
	float radius;
	unsigned int shaderProgramId;
	float arenaSizeX;
	float arenaSizeY;
	constexpr static float pi = 3.14159265358979f;
	static void updateTheta(float &thetaVal, float incrementVal)
	{
		thetaVal += incrementVal;
		if (thetaVal > 2.0f * 3.14159265f - 0.01f)
		{
		thetaVal = 0.0f;
		}
	}
};