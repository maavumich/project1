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

glm::vec2 AnimatedEntity::getCollisionVel() const
{
	return collisionVelocity;
}

glm::vec2 AnimatedEntity::getVelocitySum() const
{
	return velocity + collisionVelocity;
}

void AnimatedEntity::setVelocity(glm::vec2 vel)
{
	velocity = vel;
}

void AnimatedEntity::setCollisionVel(glm::vec2 vel)
{
	collisionVelocity = vel;
}

float AnimatedEntity::getRestitution() const
{
	return restitution;
}

void AnimatedEntity::update(unsigned dt)
{
	x += getVelocitySum()[0] * dt / 1000;
	y += getVelocitySum()[1] * dt / 1000;
	collisionVelocity -= 0.2f * collisionVelocity / mass;
}
