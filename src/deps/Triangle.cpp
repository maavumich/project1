#include "Triangle.hpp"


Triangle::Triangle(float xInit, float yInit, float yawInit, float radiusInit,
	float *color, Program *program) :
	Entity(xInit,yInit,yawInit,radiusInit,program),
	color {color[0],color[1],color[2]}
{
	glGenBuffers(1,&VBO);
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glVertexAttribPointer(program->vert(),3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(program->color(),3,GL_FLOAT,GL_FALSE,6 * sizeof(float),
		(void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Triangle::setPosition(float inX, float inY)
{
	x = inX;
	y = inY;
}

void Triangle::setAngle(float inTheta)
{
	angle = inTheta;
}

float Triangle::getXPos()
{
	return x;
}

float Triangle::getYPos()
{
	return y;
}

float Triangle::getAngle()
{
	return angle;
}


