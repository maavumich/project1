#ifndef _CIRCLE_HPP_
#define _CIRCLE_HPP_

#include "Entity.hpp"

/**
* @brief A class representing a circle in the rendered world
*/
class Circle : public Entity
{
public:
	/**
	* @brief Creates a circle with the given parameters and sets up render data
	*
	* @param xInit The initial x position
	* @param yInit The initial y position
	* @param angleInit The initial yaw
	* @param radiusInit The radius
	* @param colorIn[] The color in RGB [0,1]
	* @param program The shader program used in drawing
	*/
	Circle(float xInit,
	       float yInit,
	       float angleInit,
	       float radiusInit,
	       const float colorIn[],
	       Program *program);

	/**
	* @brief Updates the vertex data to use in rendering
	*
	* @param dt The time since the last simulation step (not used)
	*/
	virtual void update(unsigned dt);

	/**
	* @brief Draws this object in the world
	*/
	virtual void render();

private:
	// The color in RGB described by 3 values in the range [0, 1]
	float color[3];
	// The vertex buffer oject identifier
	unsigned int VBO;
	// The vertex array object identifier
	unsigned int VAO;
	// Holds the vertices to be rendered as well as the color to use
	// Will contain 360 triangles to be rendered to make a circle
	float renderData[360 * 9 * 2];
};

#endif
