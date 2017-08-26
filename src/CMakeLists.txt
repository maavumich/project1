# Builds the deps code

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include(FindPkgConfig REQUIRED)
pkg_check_modules(EPOXY REQUIRED epoxy)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

find_package(Epoxy REQUIRED)

include_directories(
	${EPOXY_INCLUDE_DIRS}
	${GTKMM_INCLUDE_DIRS}
)

add_executable(maavsquare
	main.cpp
)

target_link_libraries(maavsquare
	${EPOXY_LIBRARIES}
	${GTKMM_LIBRARIES}
)
