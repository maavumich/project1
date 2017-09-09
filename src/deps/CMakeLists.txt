set(RENDER_MODEL_RESOURCES
    win_script.sh
    image_encrypt
    win0.jpg
)

foreach (res ${RENDER_MODEL_RESOURCES})
	configure_file(${res} ${res} COPYONLY)
endforeach()

add_library(Simulation
	    AnimatedEntity.cpp
	    Circle.cpp
	    Entity.cpp
	    Obstacle.cpp
	    Program.cpp
	    Rectangle.cpp
	    Renderer.cpp
	    Roomba.cpp
	    Simulator.cpp
	    SimWindow.cpp
	    Vehicle.cpp
)

