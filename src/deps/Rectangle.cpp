#include "Rectangle.hpp"

Rectangle::Rectangle(float xInit, float yInit, float angleInit, float yawInit,
	float colorIn[], Program *program, float widthIn, float heightIn) :
	Entity(xInit,yInit,yawInit,yawInit,program),
	width {widthIn}, height {heightIn}, color {color[0],color[1],color[2]}
{
	// Creates required openGL buffers
	glGenBuffers(1,&VBO);
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&EBO);
	// Binds buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	// Create attrib pointers
	glVertexAttribPointer(program->vert(),3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)0);
	glEnableVertexAttribArray(program->vert());
	glVertexAttribPointer(program->color(),3,GL_FLOAT,GL_FALSE,6 * sizeof(float),
		(void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(program->color());
	// Create Element buffer data and store it
	unsigned int rectangleIndices[] {1,2,3,3,2,4};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(rectangleIndices),rectangleIndices,
		GL_STATIC_DRAW);
	// Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	// Sets the color in Render data, as well as depth (z)
	// Only needs to be set once
	for (int i {3}; i < 24; i += 6)
	{
		for (int ii {0}; ii < 3; ++ii)
		{
			renderData[i + ii] = color[ii];
		}
		renderData[i - 1] = 0.0f;
	}
	// Initializes the vertices
	update();
}

void Rectangle::update()
{

}
