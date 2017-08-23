#include "Entity.hpp"

Entity::Entity(float xInit, float yInit, float yawInit, float radiusInit, Program *program) :
	x {xInit}, y {yInit}, yaw {yawInit}, radius {radiusInit},
	shaderProgramId {program->prog()}
{

}

void Entity::setPosition(float inX, float inY)
{
	x = inX;
	y = inY;
}

void Entity::setYaw(float inTheta)
{
	yaw = inTheta;
}

float Entity::getXPos()
{
	return x;
}

float Entity::getYPos()
{
	return y;
}

float Entity::getYaw()
{
	return yaw;
}

float Entity::getRadius()
{
	return radius;
}