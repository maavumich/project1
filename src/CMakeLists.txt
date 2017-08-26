# Builds the deps code
include(FindPkgConfig REQUIRED)
pkg_check_modules(EPOXY REQUIRED epoxy)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
find_package(GLM REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
include_directories(
    ${EPOXY_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${GTKMM_INCLUDE_DIRS}
)
#add_executable(maavsquare
#    main.cpp
#    deps/Renderer.cpp
#    deps/Program.cpp
#    deps/SimWindow.cpp
#    deps/Simulator.cpp
#    deps/Roomba.cpp
#    deps/Obstacle.cpp
#    deps/Vehicle.cpp
#    deps/Rectangle.cpp
#    deps/Circle.cpp
#    deps/Entity.cpp
#    deps/AnimatedEntity.cpp
#)

#install(TARGETS maavsquare RUNTIME DESTINATION bin)

#target_link_libraries(maavsquare
#    ${EPOXY_LIBRARIES}
#    ${GTKMM_LIBRARIES}
#)