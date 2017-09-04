#ifndef _RECTANGLE_HPP_
#define _RECTANGLE_HPP_

#include "Entity.hpp"

/**
* @brief Class representing a rectangle in the rendered world
*/
class Rectangle : public Entity
{
public:
	/**
	* @brief Constructs a Rectangle object and sets up its render
	*
	* @param xInit The intial x position
	* @param yInit The intial y position
	* @param yawInit The intitial yaw
	* @param colorIn The color in RGB [0, 1]
	* @param program The shader program to use in drawing this objet
	* @param widthIn The width of the rectangle
	* @param heightIn The height of the rectangle
	*/
	Rectangle(float xInit,
		  float yInit,
		  float yawInit,
		  const float *colorIn,
		  Program *program,
		  float widthIn,
		  float heightIn);

	/**
	* @brief Updates location and vertex data
	*
	* @param dt Time since the last simulation step in milliseconds
	*/
	virtual void update(unsigned dt);

	/**
	* @breif Draws this object in the rendered world
	*/
	virtual void render();

	/**
	* @return The width of this rectangle
	*/
	float getWidth();

	/**
	* @return The height of this rectangle
	*/
	float getHeight();
private:
	// Characteristics by which renderData is determined
	float width;
	float height;
	float color[3];

	// Data holding the opengl object ids needed to render
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	// Holds the vertices to be put into an EBO buffer
	unsigned int rectangleIndices[6] {0,3,2,2,3,1};

	// Holds the vertices to be rendered as well as the color to use
	float renderData[24];
};

#endif
