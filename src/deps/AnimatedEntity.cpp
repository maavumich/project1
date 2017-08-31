#include "AnimatedEntity.hpp"

AnimatedEntity::AnimatedEntity(float massIn,float xInit,
			       float yInit, float yawInit,
			       float radiusInit, float restitutionInt,
			       Program *program)
	: Entity(xInit, yInit, yawInit, radiusInit, program), mass{massIn},
	forceFriction{0}, restitution{restitutionInt}
{

}

float AnimatedEntity::getMass() const
{
	return mass;
}

float AnimatedEntity::getSpeed() const
{
	return length(velocity);
}

float AnimatedEntity::getForceFriction() const{
	return Constants::coeffFriction * mass;
}

glm::vec2 AnimatedEntity::getVelocity() const
{
	return velocity;
}

void AnimatedEntity::setVelocity(glm::vec2& vel)
{
	velocity = vel;
}

float AnimatedEntity::getRestitution() const
{
	return restitution;
}

float AnimatedEntity::getYawPhysics() const
{
	return yawPhysics;
}

void AnimatedEntity::setYawPhysics(float yaw_in)
{
	yawPhysics = yaw_in;
}