#include "Shape.hpp"

class Triangle
{
public:
	Triangle(float xInit, float yInit, float angleInit, float distToVertexIn,
		float color[], unsigned int shaderProgramIdIn, float arenaSizeXIn,
		float arenaSizeYIn);
	virtual void setPosition(float inX, float inY);
	virtual void setAngle(float inTheta);
	virtual void setup();
	virtual void render();
	virtual float getXPos();
	virtual float getYPos();
	virtual float getAngle();
private:
	// Posiition, orientation, color data, as well as the shader program to use
	float x;
	float y;
	float angle;
	float distToVertex;
	float color[3];
	unsigned int shaderProgramId;
	float arenaSizeX;
	float arenaSizeY;
	// Data holding the opengl object ids needed to render
	unsigned int VBO;
	unsigned int VAO;
	// Holds the vertices to be rendered as well as the color to use
	float renderData[18];
};
