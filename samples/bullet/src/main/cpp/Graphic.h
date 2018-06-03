//
// Created by NickNovikov on 28.05.2018.
//

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace Graphic {

    struct Init_GLFW_Error {
        char *msg;

        Init_GLFW_Error(char *msg) : msg(msg) {}
    };

    struct Init_GLAD_Error {
        char *msg;

        Init_GLAD_Error(char *msg) : msg(msg) {}
    };

    struct Register_Shader_Exception {
        char *msg;
        GLchar *infoLog;

        Register_Shader_Exception(char *msg, GLchar *infoLog) : msg(msg), infoLog(infoLog) {}
    };

    GLFWwindow *initGLFW(const GLuint &width, const GLuint &height);

    void initGLAD();

    void registerShader(GLuint &shaderProgram, const std::string &vertexPath, const std::string &fragmentPath);

    GLuint loadTexture(const std::string &filepath);

}

#endif //GRAPHIC_H
