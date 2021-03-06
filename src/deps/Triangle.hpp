#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include "Entity.hpp"

class Triangle : public Entity
{
public:
	Triangle(float xInit, float yInit, float yawInit, float radiusInit,
		const float *colorIn, Program *program);
	virtual void update();
	virtual void render();
private:
	float color[3];
	// Data holding the opengl object ids needed to render
	unsigned int VBO;
	unsigned int VAO;
	// Holds the vertices to be rendered as well as the color to use
	float renderData[18];
};

#endif
