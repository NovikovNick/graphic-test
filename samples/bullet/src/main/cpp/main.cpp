#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <list>
#include <btBulletDynamicsCommon.h>


#include "Graphic.h"
#include "Cube.h"
#include "Camera.h"

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

Graphic::Camera camera = Graphic::Camera(0.0, 2.0, 0.0f, 45.0f, WIDTH, HEIGHT, 1000.0f);

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

    GLuint shaderProgram = glCreateProgram();
    Graphic::registerShader(
            shaderProgram,
            "..\\lessons\\1_8\\src\\main\\glsl\\shader.vs.glsl",
            "..\\lessons\\1_8\\src\\main\\glsl\\shader.frag.glsl"
    );

    GLuint texture = Graphic::loadTexture("..\\assets\\cube.jpg");
    std::list<Graphic::Cube> list;
    for (int i = -40; i < 40; ++i) {
        for (int z = -40; z < 40; ++z) {
            Graphic::Cube *val = new Graphic::Cube{1., i, 0, z, 0.};
            val->setTexture(texture);
            dynamicsWorld->addRigidBody(val->getBody());

            list.push_back(*val);
        }
    }
    for (float p = 1, size = 4; p < 4; ++p,size/=2) {
        for (int j = 0; j < pow(4, p); ++j){
            Graphic::Cube *val = new Graphic::Cube{size, 0, static_cast<int>(30 - size * 4), -20, 1.};
            val->setTexture(texture);
            dynamicsWorld->addRigidBody(val->getBody());
            list.push_back(*val);
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

        glUseProgram(shaderProgram);

        camera.render(shaderProgram);

        dynamicsWorld->stepSimulation(deltaTime);

        std::list<Graphic::Cube>::iterator it;
        for (it = list.begin(); it != list.end(); ++it) {
            btRigidBody* body = btRigidBody::upcast(it->getBody());

            if (body && body->getMotionState()){
                btTransform trans;
                body->getMotionState()->getWorldTransform(trans);
                it->translate(glm::vec3(float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ())));
            }

            it->render(shaderProgram);
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
        camera.moveTo(Graphic::Direction::FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        camera.moveTo(Graphic::Direction::BACK, deltaTime);
    if (keys[GLFW_KEY_A])
        camera.moveTo(Graphic::Direction::LEFT, deltaTime);
    if (keys[GLFW_KEY_D])
        camera.moveTo(Graphic::Direction::RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    camera.lookAt(xpos, ypos);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.scroll(xoffset, yoffset);
}