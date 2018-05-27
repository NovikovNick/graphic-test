cmake_minimum_required(VERSION 3.10)

project(lessons)

add_subdirectory(lib/glfw)

file(GLOB VENDOR_SRC lib/glad/src/glad.c)

include_directories(
        lib/glfw/include
        lib/glm
        lib/glad/include
)

file(GLOB LESSON_1_3_SRC "lessons/1_3/src/main/cpp/*.cpp" "lessons/1_3/src/main/cpp/*.h")
add_executable(${PROJECT_NAME}_1_3 ${LESSON_1_3_SRC} ${VENDOR_SRC})
target_link_libraries(${PROJECT_NAME}_1_3 glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})

file(GLOB LESSON_1_4_SRC "lessons/1_4/src/main/cpp/*.cpp" "lessons/1_4/src/main/cpp/*.h")
add_executable(${PROJECT_NAME}_1_4 ${LESSON_1_4_SRC} ${VENDOR_SRC})
target_link_libraries(${PROJECT_NAME}_1_4 glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})
