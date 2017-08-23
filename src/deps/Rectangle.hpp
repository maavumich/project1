#ifndef _RECTANGLE_HPP_
#define _RECTANGLE_HPP_

#include "Entity.hpp"

class Rectangle : public Entity
{
public:
	Rectangle(float xInit, float yInit, float yawInit, float radiusInit,
		float colorIn[], Program *program, float widthIn, float heightIn);
	virtual void update();
	virtual void render();
private:
	// Characteristics by which renderData is determined
	float width;
	float height;
	float color[3];
	// Data holding the opengl object ids needed to render
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	// Holds the vertices to be rendered as well as the color to use
	float renderData[24];
};

#endif
