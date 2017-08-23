#include "Triangle.hpp"


Triangle::Triangle(float xInit, float yInit, float yawInit, float radiusInit,
	float *color, Program *program) :
	Entity(xInit,yInit,yawInit,radiusInit,program),
	color {color[0],color[1],color[2]}
{
	// Creates required openGL buffers and creates attrib pointers
	glGenBuffers(1,&VBO);
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glVertexAttribPointer(program->vert(),3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)0);
	glEnableVertexAttribArray(program->vert());
	glVertexAttribPointer(program->color(),3,GL_FLOAT,GL_FALSE,6 * sizeof(float),
		(void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(program->color());
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	// Sets the color in Render data, as well as depth (z)
	// Only needs to be set once
	for (int i {3}; i < 18; i += 6)
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

void Triangle::update()
{
	for (int i {0}; i < 3; ++i)
	{
		renderData[i * 6] = cos(yaw + i * (2 * PI / 3)) * radius;
		renderData[i * 6 + 1] = sin(yaw + i * (2 * PI / 3)) * radius;
	}
}

void Triangle::render()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(renderData),renderData,GL_STREAM_DRAW);
	glDrawArrays(GL_TRIANGLES,0,3);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
}
