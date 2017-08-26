#include "Renderer.hpp"

using std::cerr;

Renderer::Renderer()
{
	cur_size.x = 800;
	cur_size.y = 800;
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
	glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void Renderer::recreateRenderBuffers()
{
	glBindFramebuffer(GL_FRAMEBUFFER,offsFB);
	glDeleteRenderbuffers(2,offsRBS.data());
	glGenRenderbuffers(2,offsRBS.data());
	glBindRenderbuffer(GL_RENDERBUFFER,offsRBS[0]);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_RGB,cur_size.x,cur_size.y);
	glBindRenderbuffer(GL_RENDERBUFFER,0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,
		GL_RENDERBUFFER,offsRBS[0]);
	glBindRenderbuffer(GL_RENDERBUFFER,offsRBS[1]);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT16,
		cur_size.x,cur_size.y);
	glBindRenderbuffer(GL_RENDERBUFFER,0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,
		GL_RENDERBUFFER,offsRBS[1]);
	glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void Renderer::render(const std::vector<Vehicle> &vehicles, const std::vector<Roomba> &roombas,
	const std::vector<Obstacle> &obstacles)
{
	//recreateRenderBuffers();
	glBindFramebuffer(GL_FRAMEBUFFER,offsFB);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glClear(GL_COLOR_BUFFER_BIT);
	// Check the frame buffer status
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		cerr << "FRAMEBUFFER ISSUES DETECTED!\n";
		cerr << "Your error is: " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << "\n";
		cerr << "Codes are:\n";
		cerr << "\t" << GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT << " incomplete attachment\n";
		cerr << "\t" << GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS << " incomplete dimensions\n";
		cerr << "\t" << GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT << " incomplete missing attachment\n";
		cerr << "\t" << GL_FRAMEBUFFER_UNSUPPORTED << " unsupported\n";
		exit(-1);
	}
	if (Constants::changeColors)
	{
		glClearColor(color[0],color[1],color[2],1.0f);
		updateColor();
	}
	else
	{
		glClearColor(Constants::clearColor[0],Constants::clearColor[1],
			Constants::clearColor[2],1.0f);
	}
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
	glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void Renderer::updateColor()
{
	color[0] += Constants::changeColor[0];
	color[1] += Constants::changeColor[1];
	color[2] += Constants::changeColor[2];
}

Program* Renderer::getProgram()
{
	return &program;
}

void Renderer::blit()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER,offsFB);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glBlitFramebuffer(0,0,cur_size.x,cur_size.y,0,0,cur_size.x,cur_size.y,
		GL_COLOR_BUFFER_BIT,GL_NEAREST);
	glBindFramebuffer(GL_READ_FRAMEBUFFER,0);
}

void Renderer::resize(const glm::ivec2& size)
{
	glBindFramebuffer(GL_FRAMEBUFFER,offsFB);
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
	glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void Renderer::addRectangle(float xInit, float yInit, float yawInit, float radiusInit,
	float colorIn[], Program *program, float widthIn, float heightIn)
{
	field.emplace_back(xInit,yInit,yawInit,radiusInit,colorIn,program,widthIn,heightIn);
}
