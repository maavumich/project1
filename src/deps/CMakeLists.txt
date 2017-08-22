
# Builds the deps code

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include(FindPkgConfig REQUIRED)
pkg_check_modules(EPOXY REQUIRED epoxy)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

find_package(Epoxy REQUIRED)
find_package(GLM REQUIRED)

include_directories(
	${EPOXY_INCLUDE_DIRS}
	${GTKMM_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}
)

