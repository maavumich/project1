#ifndef SIM_WINDOW_HPP
#define SIM_WINDOW_HPP

/**
* @file SimWindow.hpp
*
* This file contains the Gtk Window used by the window manager and the GLArea to which openGL will
* render its scenes. It also accepts input from the keyboard based on handlers which the user
* attaches.
*
* @author Romario Pashollari (rpash@umich.edu)
*/

#include <memory>
#include <functional>
#include <map>

#include <gtkmm.h>
#include <gdk/gdk.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/glarea.h>
#include <gtkmm/grid.h>
#include <glibmm/main.h>

#include "Renderer.hpp"
#include "Simulator.hpp"


// Number of frames to try to generate per second (FPS is capped at this)
constexpr unsigned FPS{60};

// The simulation time step in milliseconds calculated based on FPS above
constexpr unsigned SIMULATION_DT_MS{1000 / FPS};

/**
* @brief RenderArea provides a widget-style interface for using the Renderer with a Simulator.
*/
class RenderArea : public Gtk::GLArea
{
public:
	/**
	* @brief Constructs a GLArea for the Renderer to draw on
	*/
	RenderArea();

private:
	// The renderer which draws in this area
	std::unique_ptr<Renderer> renderer;

	// Sets up a new renderer when the window is mapped.
	void on_map();

	// Cleans up the current renderer when the window is unmapped.
	void on_unmap();

	// Resizes the window on appropriate signal. If there is no renderer, does nothing
	void on_resize(int width, int height);

	// If there is a renderer, processes any buffer requests, if there are any, and Redraws
	// the scene. If there is not a renderer, does nothing.
	bool on_render(const Glib::RefPtr<Gdk::GLContext>&);
}; // class RenderArea

///////////////////////////////////////////Window//////////////////////////////////////////////////

/**
* @brief Handles displaying the simulation and takes in keyboard input
*/
class SimWindow : public Gtk::Window
{
public:
	/**
	* @brief Sets up a window for display
	*/
	SimWindow();

	/**
	* @brief Disconnects the timeout function
	*/
	~SimWindow();

	/**
	* @brief Attach an event handler to this window.
	*
	* @details In order to abstract the Window manager and Renderer, this function makes it
	* possible to add the key and handler to a map of keyboark key-handler map. If there already
	* exists a handler for the key, that handler will be replaced.
	* The event must be passed in as a GDK keysym. A list can be found here:
	* https://git.gnome.org/browse/gtk+/tree/gdk/gdkkeysyms.h
	* The `func` parameter can be either a function pointer, a functor, or a lambda.
	*
	* @param key The event (as an int) which this event handler is associated with.
	* @param func The function that handles this event. It operates on the simulator
	*
	* @return True if this event handler is new, false if it replaced a previous event handler
	*/
	bool attachEventHandler(int key, const std::function<void(Simulator)> func);

protected:
	/**
	* @brief Handles the key release event based on attached handlers. Does nothing if no
	* handler is attached for a key.
	*
	* @return True to stop signal propagation, false otherwise (This always returns true)
	*/
	bool on_key_release();

private:
	// Holds the OpenGL rendered field
	RenderArea renderArea;

	// The Simulator
	Simulator sim;

	// Container for RenderArea and other widgets that need to be added
	Gtk::Grid layoutGrid;

	// Timer used for render steps
	sigc::connection timeout;

	// Container for all attached key handlers
	std::map<int, std::function<void(Simulator)> > keyHandlers;
}; // Class SimWindow

#endif
