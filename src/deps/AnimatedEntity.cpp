#include "AnimatedEntity.hpp"

AnimatedEntity::AnimatedEntity(float speedIn, float massIn,float xInit, float yInit, float yawInit,
	float radiusInit, Program *program) : Entity(xInit,yInit,yawInit,radiusInit,program),
	mass {massIn}, speed {speedIn}
{

}

int AnimatedEntity::getMass()
{
	return mass;
}

float AnimatedEntity::getSpeed()
{
	return speed;
}

void AnimatedEntity::setSpeed(float newSpeed)
{
	speed = newSpeed;
}
