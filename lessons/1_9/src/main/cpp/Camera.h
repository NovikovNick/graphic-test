//
// Created by NickNovikov on 03.06.2018.
//

#ifndef LESSONS_CAMERA_H
#define LESSONS_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace Graphic {

    enum Direction {
        RIGHT, LEFT, FORWARD, BACK
    };

    class Camera {
    private:

        glm::vec3 cameraPos, cameraFront, cameraUp;
        float yaw, pitch;
        float fieldOfView;

        int width;
        int height;
        int range;
        GLfloat cameraSpeed;

        bool firstMouse;
        GLfloat lastX;
        GLfloat lastY;
    public:

        Camera(const float &x, const float &y, const float &z,
               const float &fieldOfView, const int &width, const int &height, const int &range)
                : cameraPos(glm::vec3(x, y, z)),
                  cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
                  cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
                  fieldOfView(fieldOfView), width(width), height(height),  range(range),
                  firstMouse(true),
                  lastX((GLfloat)width/2),
                  lastY((GLfloat)height/2),
                  yaw( -90.0f), pitch(0.0f),
                  cameraSpeed(10.0f) {}

        void lookAt(const double &xpos, const double &ypos);

        void scroll(const double &xoffset, const double &yoffset);

        void moveTo(Direction direction, const float &delta);

        void render(const GLuint &shaderProgram);
    };
}


#endif //LESSONS_CAMERA_H
