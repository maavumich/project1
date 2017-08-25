#include "deps/SimWindow.hpp"

// Write event handler function prototypes here

int main(int argc, char** argv)
{
	auto app = Gtk::Application::create(argc, argv, "org.maav.training.simulation");
	SimWindow win{};

	// Attach event handlers here

	return app->run(win);
}

// Write event handler function implementations here

// Function Pointers for simulator class, passed to simwindow and used to create
// Roomba and Obstacle

// Modifies: Roomba object
// Effects:  Gurantees that the roomba will stay in bounds
void updateRoombaLocation(Roomba& roomba)
{
	
}