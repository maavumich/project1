#ifndef _AENTITY_HPP_
#define _AENTITY_HPP_

#include "Entity.hpp"

class AnimatedEntity: public Entity
{
public:
	AnimatedEntity(float speedIn, float massIn,float xInit, float yInit, float yawInit,
		float radiusInit, Program *program);
	int getMass();
	float getSpeed();
	void setSpeed(float newSpeed);

protected:
	int mass;
	float speed = 0; //default zero
	float forceFriction;
};

#endif
