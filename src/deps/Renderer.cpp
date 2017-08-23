#include "Renderer.hpp"

void Renderer::render(Entity *vehicle, std::vector<Entity*> &roombas,
	std::vector<Entity*> &obstacles, std::vector<Entity*> &rectangles)
{
	for (auto rectangle : rectangles)
	{
		rectangle->update();
		rectangle->render();
	}
	for (auto roomba : roombas)
	{
		roomba->update();
		roomba->render();
	}
	for (auto obstacle : obstacles)
	{
		obstacle->update();
		obstacle->render();
	}
	// Renders the vehicle last
	vehicle->update();
	vehicle->render();
}

