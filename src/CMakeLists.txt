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
add_executable(spooky-thing
	main.cpp
)

install(TARGETS spooky-thing RUNTIME DESTINATION bin)

target_link_libraries(spooky-thing
	Simulation
	${EPOXY_LIBRARIES}
	${GTKMM_LIBRARIES}
)

add_subdirectory(deps)
