#ifndef _AENTITY_HPP_
#define _AENTITY_HPP_

#include "Entity.hpp"

/**
* @brief An entity that moves
*/
class AnimatedEntity: public Entity
{
public:
	/**
	* @brief Constructs an AnimatedEntity given the following paramters. Also sets up rendering
	* for this AnimatedEntity
	*
	* @param massIn The mass
	* @param xInit The initial x position
	* @param yInit The initial y position
	* @param yawInit The initial yaw
	* @param radiusInit The radius of the body
	* @param restitutionInt The restitution (bounciness)
	* @param program The shader program to use when drawing
	*/
	AnimatedEntity(float massIn,
		       float xInit,
		       float yInit,
		       float yawInit,
		       float radiusInit,
		       float restitutionInt,
		       Program *program);

	/**
	* @return The mass
	*/
	float getMass() const;

	/**
	* @return The speed as a scalar
	*/
	float getSpeed() const;

	/**
	* @return The force of friction as a scalar
	*/
	float getForceFriction() const;

	/**
	* @return The velocity vector not caused by collision
	*/
	glm::vec2 getVelocity() const;

	/**
	* @return The velocity vector caused by collision
	*/
	glm::vec2 getCollisionVel() const;

	/**
	* @return The net velocity vector
	*/
	glm::vec2 getVelocitySum() const;

	/**
	* @return The restitution
	*/
	float getRestitution() const;

	/**
	* @brief Sets the movement velocity
	*
	* @param vel The velocity to set
	*/
	void setVelocity(glm::vec2 vel);

	/**
	* @brief Sets the collision velocity
	*
	* @param vel The velocity to set
	*/
	void setCollisionVel(glm::vec2 vel);

	/**
	* @brief Changes position based on `velocity` and `dt`
	*
	* @param dt The change in time since the last simulation step in milliseconds
	*/
	virtual void update(unsigned dt);

protected:
	// Physical data
	float mass;
	float forceFriction;
	glm::vec2 velocity{0.f, 0.f};
	glm::vec2 collisionVelocity{0.f, 0.f};
	float restitution;
};

#endif
