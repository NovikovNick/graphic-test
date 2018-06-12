cmake_minimum_required(VERSION 3.10)

project(lessons)

find_package(OpenGL REQUIRED)


add_subdirectory(lib/glfw)
add_subdirectory(lib/soil)

option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
add_subdirectory(lib/bullet)

file(GLOB VENDOR_SRC lib/glad/src/glad.c)

include_directories(
        lib/glfw/include
        lib/glm
        lib/glad/include
        lib/soil/src
        lib/bullet/src
)

file(GLOB LESSON_1_3_SRC "lessons/1_3/src/main/cpp/*.cpp" "lessons/1_3/src/main/cpp/*.h")
add_executable(${PROJECT_NAME}_1_3 ${LESSON_1_3_SRC} ${VENDOR_SRC})
target_link_libraries(${PROJECT_NAME}_1_3 glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})

file(GLOB LESSON_1_4_SRC "lessons/1_4/src/main/cpp/*.cpp" "lessons/1_4/src/main/cpp/*.h")
add_executable(${PROJECT_NAME}_1_4 ${LESSON_1_4_SRC} ${VENDOR_SRC})
target_link_libraries(${PROJECT_NAME}_1_4 glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})

file(GLOB LESSON_1_5_SRC "lessons/1_5/src/main/cpp/*.cpp" "lessons/1_5/src/main/cpp/*.h")
add_executable(${PROJECT_NAME}_1_5 ${LESSON_1_5_SRC} ${VENDOR_SRC})
target_link_libraries(${PROJECT_NAME}_1_5 glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})

file(GLOB LESSON_1_6_SRC "lessons/1_6/src/main/cpp/*.cpp" "lessons/1_6/src/main/cpp/*.h")
add_executable(${PROJECT_NAME}_1_6 ${LESSON_1_6_SRC} ${VENDOR_SRC})
target_link_libraries(${PROJECT_NAME}_1_6 SOIL glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})

file(GLOB LESSON_1_7_SRC "lessons/1_7/src/main/cpp/*.cpp" "lessons/1_7/src/main/cpp/*.h")
add_executable(${PROJECT_NAME}_1_7 ${LESSON_1_7_SRC} ${VENDOR_SRC})
target_link_libraries(${PROJECT_NAME}_1_7 SOIL glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})

file(GLOB LESSON_1_8_SRC "lessons/1_8/src/main/cpp/*.cpp" "lessons/1_8/src/main/cpp/*.h")
add_executable(${PROJECT_NAME}_1_8 ${LESSON_1_8_SRC} ${VENDOR_SRC})
target_link_libraries(${PROJECT_NAME}_1_8 SOIL glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})

file(GLOB LESSON_1_9_SRC "lessons/1_9/src/main/cpp/*.cpp" "lessons/1_9/src/main/cpp/*.h")
add_executable(${PROJECT_NAME}_1_9 ${LESSON_1_9_SRC} ${VENDOR_SRC})
target_link_libraries(${PROJECT_NAME}_1_9 SOIL glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})

file(GLOB SAMPLE_1_SRC "samples/bullet/src/main/cpp/**/*.cpp" "samples/bullet/src/main/cpp/**/*.h" "samples/bullet/src/main/cpp/*.cpp" "samples/bullet/src/main/cpp/*.h")
add_executable(${PROJECT_NAME}_SAMPLE_1 ${SAMPLE_1_SRC} ${VENDOR_SRC})
target_link_libraries(${PROJECT_NAME}_SAMPLE_1 BulletDynamics BulletCollision LinearMath SOIL glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})

file(GLOB LESSON_2_1_SRC "lessons/2_1/src/main/cpp/**/*.cpp" "lessons/2_1/src/main/cpp/**/*.h" "lessons/2_1/src/main/cpp/*.cpp" "lessons/2_1/src/main/cpp/*.h")
add_executable(${PROJECT_NAME}_2_1 ${LESSON_2_1_SRC} ${VENDOR_SRC})
target_link_libraries(${PROJECT_NAME}_2_1 BulletDynamics BulletCollision LinearMath SOIL glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})

file(GLOB LESSON_2_2_SRC "lessons/2_2/src/main/cpp/**/*.cpp" "lessons/2_2/src/main/cpp/**/*.h" "lessons/2_2/src/main/cpp/*.cpp" "lessons/2_2/src/main/cpp/*.h")
add_executable(${PROJECT_NAME}_2_2 ${LESSON_2_2_SRC} ${VENDOR_SRC})
target_link_libraries(${PROJECT_NAME}_2_2 BulletDynamics BulletCollision LinearMath SOIL glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})

file(GLOB LESSON_2_3_SRC "lessons/2_3/src/main/cpp/**/*.cpp" "lessons/2_3/src/main/cpp/**/*.h" "lessons/2_3/src/main/cpp/*.cpp" "lessons/2_3/src/main/cpp/*.h")
add_executable(${PROJECT_NAME}_2_3 ${LESSON_2_3_SRC} ${VENDOR_SRC})
target_link_libraries(${PROJECT_NAME}_2_3 BulletDynamics BulletCollision LinearMath SOIL glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})
