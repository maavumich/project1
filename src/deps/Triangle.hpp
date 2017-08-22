#include "Entity.hpp"

class Triangle : public Entity
{
public:
	Triangle(float xInit, float yInit, float angleInit, float distToVertexIn,
		float color[], unsigned int shaderProgramIdIn, float arenaSizeXIn,
		float arenaSizeYIn);
	virtual void setup();
	virtual void render();
private:
	float color[3];
	// Data holding the opengl object ids needed to render
	unsigned int VBO;
	unsigned int VAO;
	// Holds the vertices to be rendered as well as the color to use
	float renderData[18];
};
