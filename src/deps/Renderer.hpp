#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <array>
#include <vector>

#include <epoxy/gl.h> // OpenGL function pointer manager
#include <glm/glm.hpp> // OpenGL math library

#include "Program.hpp"
#include "Entity.hpp"

class Renderer
{
public:

	Renderer();

	/**
	* @brief Draws a scene to the offscreen framebuffer given current state of
	* the simulator objects
	*
	* @param INCLUDE ANY PARAMS NECESSARY FOR SIMULATOR OBJECTS
	* Pass in the vectors of Entity* to be rendered as well as the vehicle
	* as an Entity*
	*/
	void render(Entity *vehicle, std::vector<Entity*> &roombas,
		std::vector<Entity*> &obstacles, std::vector<Entity*> &rectangles);

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

	Program* getProgram();

private:
	// Offscreen rendering objects
	GLuint offsFB; // offscreen framebuffer
	std::array<GLuint, 2> offsRBS; //offscreen renderbuffers

	// Shader program class that holds the shader program and ids of certain things
	Program program;

	// Current image size
	glm::ivec2 cur_size;
};

#endif
