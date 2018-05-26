cmake_minimum_required(VERSION 3.10)

find_package(OpenGL REQUIRED)

project(fst_steps)

set(CMAKE_CXX_STANDARD 11)


#file(GLOB SOURCES "*.cpp" "*.h")
set(SOURCES "main.cpp")

include_directories(lib/glfw/include)
include_directories(lib/glm)

add_executable(fst_steps ${SOURCES})

add_subdirectory(lib/glfw)


target_link_libraries(fst_steps glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})