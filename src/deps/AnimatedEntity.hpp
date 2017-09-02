#ifndef _AENTITY_HPP_
#define _AENTITY_HPP_

#include "Entity.hpp"

class AnimatedEntity: public Entity
{
public:
	AnimatedEntity(float massIn,
		       float xInit,
		       float yInit,
		       float yawInit,
		       float radiusInit,
		       float restitutionInt,
		       Program *program);
	float getMass() const;
	float getSpeed() const;
	float getForceFriction() const;
	glm::vec2 getVelocity() const;
	glm::vec2 getCollisionVel() const;
	glm::vec2 getVelocitySum() const;
	float getRestitution() const;
	void setVelocity(glm::vec2 vel);
	void setCollisionVel(glm::vec2 vel);
	virtual void update(unsigned dt);

	float getForceFriction() const;
	glm::vec2 getVelocity() const;
	float getRestitution() const;
	void setVelocity(glm::vec2& vel);

	float getYawPhysics() const;
	void setYawPhysics(float yaw_in);

protected:
	float mass;
	float forceFriction;
	glm::vec2 velocity{0.f, 0.f};
	glm::vec2 collisionVelocity{0.f, 0.f};
	float restitution;
};

#endif
