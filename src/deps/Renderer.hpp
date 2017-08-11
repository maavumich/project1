#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <array>

#include <epoxy/gl.h> // OpenGL function pointer manager
#include <glm/glm.hpp> // OpenGL math library

class Renderer
{
public:
	/**
	* @brief Draws a scene to the offscreen framebuffer given current state of
	* the simulator objects
	*
	* @param INCLUDE ANY PARAMS NECESSARY FOR SIMULATOR OBJECTS
	*/
	void draw();

	/**
	* @brief Blits the drawn scene from the offscreen framebuffer to the
	* currently bound framebuffer
	*/
	void blit();

	/**
	* @breif Updates the renderer to use a new framebuffer size
	*
	* @param size The new size to render with
	*/
	void resize(const glm::ivec2& size);

private:
	// Offscreen rendering objects
	GLuint offsFB; // offscreen framebuffer
	std::array<GLuint, 2> offsRBS; //offscreen renderbuffers

	// Current image size
	glm::ivec2 cur_size;
};

#endif
