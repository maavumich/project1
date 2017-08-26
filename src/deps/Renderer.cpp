#include "Renderer.hpp"

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

}

void Renderer::resize(const glm::ivec2& size)
{

}
