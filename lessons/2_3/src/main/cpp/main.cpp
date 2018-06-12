#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <btBulletDynamicsCommon.h>
#include <BulletSoftBody/btSoftBodyInternals.h>


#include "include/Graphic.h"

using namespace std;


GLFWwindow *window;
bool isWireFrameState = false;

//it is better to use GL primitive type instead predefined
//const GLuint WIDTH =  1920, HEIGHT = 1080;
const GLuint WIDTH = 1080, HEIGHT = 768;

bool keys[1024];

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void do_movement();



//map<string, shared_ptr<Graphic::Model>> initModels();

Graphic::Camera camera = Graphic::Camera(glm::vec3(0.0f, 2.0f, 17.0f));

GLfloat deltaTime = 0.0f;    // Время, прошедшее между последним и текущим кадром
GLfloat lastFrame = 0.0f;    // Время вывода последнего кадра

int main() {

    window = Graphic::initGLFW(WIDTH, HEIGHT);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    Graphic::initGLAD();

    glViewport(0, 0, WIDTH, HEIGHT);

    Graphic::Scene scene = Graphic::Scene("..\\assets\\scene.txt");

    int sec = 0;
    // Game loop
    while (!glfwWindowShouldClose(window)) {

        GLfloat currentFrame = glfwGetTime();

        if (sec < static_cast<int>(currentFrame)) {
            std::cout << (sec = static_cast<int>(currentFrame)) << std::endl;
        }

        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        do_movement();

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render
        glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        scene.render(camera, currentFrame);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }


    /////////CLEANUP/////////

    // Terminates GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
        if (isWireFrameState) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        isWireFrameState = !isWireFrameState;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (action == GLFW_PRESS)
        keys[key] = true;
    else if (action == GLFW_RELEASE)
        keys[key] = false;

}

void do_movement() {
    if (keys[GLFW_KEY_W])
        camera.moveTo(Graphic::Camera_Movement::FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        camera.moveTo(Graphic::Camera_Movement::BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A])
        camera.moveTo(Graphic::Camera_Movement::LEFT, deltaTime);
    if (keys[GLFW_KEY_D])
        camera.moveTo(Graphic::Camera_Movement::RIGHT, deltaTime);
}


bool firstMouse = true;
GLfloat lastX;
GLfloat lastY;

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    camera.lookAt(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.zoom((GLfloat) yoffset);
}

