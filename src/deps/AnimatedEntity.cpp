#include "AnimatedEntity.hpp"

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