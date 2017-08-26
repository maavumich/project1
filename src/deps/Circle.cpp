#include "Circle.hpp"

Circle::Circle(float xInit, float yInit, float yawInit, float radiusInit,
	const float *colorIn, Program *program) :
	Entity(xInit,yInit,yawInit,radiusInit,program)
{
	// Initialize color
	color[0] = colorIn[0];
	color[1] = colorIn[1];
	color[2] = colorIn[2];
	// Creates required openGL buffers and creates attrib pointers
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(renderData), renderData, GL_STREAM_DRAW);
	glEnableVertexAttribArray(program->vert());
	glVertexAttribPointer(program->vert(), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
		(GLvoid*)0);
	glEnableVertexAttribArray(program->color());
	glVertexAttribPointer(program->color(), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
		(GLvoid*)(sizeof(float) * 3));

	// Sets the color in Render data, as well as depth (z)
	// Only needs to be set once
	for (int i {3}; i < 720 * 9; i += 6)
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

Circle::~Circle() noexcept
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Circle::update()
{
	float thetas[3] {0.0f, 2.0f * PI / 3.0f, 4.0f * PI / 3.0f};
	for (int i {0}; i < 18 * 360; i += 18)
	{
		for (int ii {0}; ii < 3; ++ii)
		{
			renderData[i + 6 * ii] = x + cos(thetas[ii]) * radius;
			renderData[i + 6 * ii] = renderData[i + 6 * ii] / ARENASIZEX;
			renderData[i + 1 + 6 * ii] = y + sin(thetas[ii]) * radius;
			renderData[i + 1 + 6 * ii] = renderData[i + 1 + 6 * ii] / ARENASIZEY;
			updateTheta(thetas[ii], 2 * PI / (3 * 359));
		}
	}
}

void Circle::render() const
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 360 * 3);
}
