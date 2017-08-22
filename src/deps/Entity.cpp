#include "Entity.hpp"

Entity::Entity(float xInit, float yInit, float angleInit, float radiusInit,
	unsigned int shaderProgramIdIn, float arenaSizeXIn, float arenaSizeYIn) :
	x {xInit}, y {yInit}, angle {angleInit}, radius {radiusInit},
	shaderProgramId {shaderProgramIdIn}, arenaSizeX {arenaSizeXIn}, arenaSizeY {arenaSizeYIn}
{

}

void Entity::setPosition(float inX, float inY)
{
	x = inX;
	y = inY;
}

void Entity::setAngle(float inTheta)
{
	angle = inTheta;
}

float Entity::getXPos()
{
	return x;
}

float Entity::getYPos()
{
	return y;
}

float Entity::getAngle()
{
	return angle;
}
