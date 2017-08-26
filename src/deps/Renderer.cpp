#include "Renderer.hpp"

Renderer::Renderer()
{
	cur_size.x = 800;
	cur_size.y = 600;
	glViewport(0,0,cur_size.x,cur_size.y);
	// Create frame buffer
	glGenFramebuffers(1,&offsFB);
	glGenRenderbuffers(2,offsRBS.data());
	glBindFramebuffer(GL_FRAMEBUFFER,offsFB);
	// Color render buffer setup
	glBindRenderbuffer(GL_RENDERBUFFER,offsRBS[0]);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_RGB,cur_size.x,cur_size.y);
	glBindRenderbuffer(GL_RENDERBUFFER,0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,
		GL_RENDERBUFFER,offsRBS[0]);
	glBindRenderbuffer(GL_RENDERBUFFER,0);
	// Depth render buffer setup
	glBindRenderbuffer(GL_RENDERBUFFER,offsRBS[1]);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT16,
		cur_size.x,cur_size.y);
	glBindRenderbuffer(GL_RENDERBUFFER,0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,
		GL_RENDERBUFFER,offsRBS[1]);
	// Don't need to unbind because there is only one frame buffer
}

void Renderer::render(const std::vector<Vehicle> &vehicles, const std::vector<Roomba> &roombas,
	const std::vector<Obstacle> &obstacles)
{
	for (auto rectangle : field)
	{
		rectangle.render();
	}
	for (auto roomba : roombas)
	{
		roomba.update();
		roomba.render();
	}
	for (auto obstacle : obstacles)
	{
		obstacle.update();
		obstacle.render();
	}
	// Renders the vehicle last
	for (auto vehicle : vehicles)
	{
		vehicle.update();
		vehicle.render();
	}
}

Program* Renderer::getProgram()
{
	return &program;
}

void Renderer::blit()
{
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glBlitFramebuffer(0,0,cur_size.x,cur_size.y,0,0,cur_size.x,cur_size.y,
		GL_COLOR_BUFFER_BIT,GL_NEAREST);
}

void Renderer::resize(const glm::ivec2& size)
{
	glViewport(0,0,size.x,size.y);
	// Change color render buffer
	glBindRenderbuffer(GL_RENDERBUFFER,offsRBS[0]);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_RGB,size.x,size.y); // TODO TODO
	glBindRenderbuffer(GL_RENDERBUFFER,0);
	glBindRenderbuffer(GL_RENDERBUFFER,0);
	// Change depth render buffer
	glBindRenderbuffer(GL_RENDERBUFFER,offsRBS[1]);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT16,
		size.x,size.y);
	cur_size = size;
}

void Renderer::addRectangle(float xInit, float yInit, float yawInit, float radiusInit,
	float colorIn[], Program *program, float widthIn, float heightIn)
{
	field.emplace_back(xInit,yInit,yawInit,radiusInit,colorIn,program,widthIn,heightIn);
}
