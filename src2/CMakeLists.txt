
# Builds the opengl tutorial
find_package(GLM REQUIRED)
find_package(Epoxy REQUIRED)
find_package(glfw3 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(
	SYSTEM
	${EPOXY_INCLUDE_DIRS}
	${EIGEN3_INCLUDE_DIR}
	${GLM_INCLUDE_DIRS}
)

add_executable(tutorial tutorial1.cpp ../src/deps/Program.cpp)

add_executable(test test.cpp ../src/deps/Program.cpp)

target_link_libraries(tutorial
	${EPOXY_LIBRARIES}
	${GLFW3_LIBRARIES}
)

target_link_libraries(test
	${EPOXY_LIBRARIES}
	)
