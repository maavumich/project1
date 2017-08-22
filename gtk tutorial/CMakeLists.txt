
# Builds the gtk+ tutorial

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

add_executable(example
	example-0.c
)

target_link_libraries(example
	${EPOXY_LIBRARIES}
	${GTKMM_LIBRARIES}
)

add_executable(example2
	example-1.c
)

target_link_libraries(example2
	${EPOXY_LIBRARIES}
	${GTKMM_LIBRARIES}
)
