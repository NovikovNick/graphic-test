project(lesson_1_3)

set(LIPRARY_PATH ../../lib)

file(GLOB SOURCES "src/main/cpp/*.cpp" "src/main/cpp/*.h")
file(GLOB VENDORS_SOURCES ${LIPRARY_PATH}/glad/src/glad.c)

include_directories(
        ${LIPRARY_PATH}/glfw/include
        ${LIPRARY_PATH}/glm
        ${LIPRARY_PATH}/glad/include
)

add_executable(${PROJECT_NAME} ${SOURCES} ${VENDORS_SOURCES})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})

