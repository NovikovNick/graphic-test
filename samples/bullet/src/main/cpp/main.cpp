#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <list>
#include <btBulletDynamicsCommon.h>
#include <BulletSoftBody/btSoftBodyInternals.h>


#include "include/Graphic.h"

GLFWwindow *window;
bool isWireFrameState = false;

//it is better to use GL primitive type instead predefined
//const GLuint WIDTH =  1920, HEIGHT = 1080;
const GLuint WIDTH =  1080, HEIGHT = 768;

bool keys[1024];

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void do_movement();

Graphic::Camera camera = Graphic::Camera(glm::vec3(0.0f, 5.0f, 11.0f));

GLfloat deltaTime = 0.0f;    // Время, прошедшее между последним и текущим кадром
GLfloat lastFrame = 0.0f;    // Время вывода последнего кадра

int main() {

    ///START INIT BULLET////
    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -10, 0));
    ///END INIT BULLET////

    window = Graphic::initGLFW(WIDTH, HEIGHT);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    Graphic::initGLAD();

    glViewport(0, 0, WIDTH, HEIGHT);

    Graphic::Cube model = Graphic::Cube();

    std::list<Graphic::GameObject> list;
    for (float z = -12; z < 12; ++z) {
        for (int x = -12; x < 12; ++x) {
            Graphic::GameObject object = Graphic::GameObject(model, glm::vec3(x, 0, z), 1.0f, 0.0f);
            dynamicsWorld->addRigidBody(object.ptrRigidBody);
            list.push_back(object);

            Graphic::GameObject top = Graphic::GameObject(model, glm::vec3(x, 12, z), 1.0f, 0.0f);
            dynamicsWorld->addRigidBody(top.ptrRigidBody);
            list.push_back(top);
        }
    }
    for (float y = 1; y < 12; ++y) {
        for (int x = -12; x < 12; ++x) {
            Graphic::GameObject object = Graphic::GameObject(model, glm::vec3(x, y, -12), 1.0f, 0.0f);
            dynamicsWorld->addRigidBody(object.ptrRigidBody);
            list.push_back(object);

            Graphic::GameObject top = Graphic::GameObject(model, glm::vec3(x, y, 12), 1.0f, 0.0f);
            dynamicsWorld->addRigidBody(top.ptrRigidBody);
            list.push_back(top);
        }
    }
    for (float y = 1; y < 12; ++y) {
        for (int z = -12; z < 12; ++z) {
            Graphic::GameObject object = Graphic::GameObject(model, glm::vec3(-12, y, z), 1.0f, 0.0f);
            dynamicsWorld->addRigidBody(object.ptrRigidBody);
            list.push_back(object);

            Graphic::GameObject top = Graphic::GameObject(model, glm::vec3(12, y, z), 1.0f, 0.0f);
            dynamicsWorld->addRigidBody(top.ptrRigidBody);
            list.push_back(top);
        }
    }



    // Game loop
    while (!glfwWindowShouldClose(window)) {

        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        do_movement();

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render
        glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        dynamicsWorld->stepSimulation(deltaTime);

        std::list<Graphic::GameObject>::iterator it;
        for (it = list.begin(); it != list.end(); ++it) {

            it->render(camera);
        }

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }


    /////////CLEANUP/////////

    //delete dynamics world
    delete dynamicsWorld;
    delete solver;
    delete overlappingPairCache;
    delete dispatcher;
    delete collisionConfiguration;

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