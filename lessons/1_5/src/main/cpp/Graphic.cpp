//
// Created by NickNovikov on 28.05.2018.
//

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Graphic.h"

using namespace Graphic;
using namespace std;

GLFWwindow *Graphic::initGLFW(const GLuint &width, const GLuint &height) {
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//avoid old function
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window_ptr = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
    if (window_ptr == nullptr) {
        throw Init_GLFW_Error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window_ptr);

    return window_ptr;
}

void Graphic::initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw Init_GLAD_Error("Failed to initialize OpenGL context");
    }
}

void registerOneShader(GLuint &shaderProgram, GLenum shaderType, const string &shader_src) {

    cout << shader_src << endl;

    GLuint shader = glCreateShader(shaderType);
    const GLchar *str = shader_src.c_str();
    glShaderSource(shader, 1, &str, NULL);
    glCompileShader(shader);

    // Check for compile time errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        glDeleteShader(shader);
        throw Register_Shader_Exception("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
    }

    glAttachShader(shaderProgram, shader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        glDeleteShader(shader);
        throw Register_Shader_Exception("ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n", infoLog);

    }

    glDeleteShader(shader);
}



string loadGLSL(const string &shaderPath) {

    // 1. Получаем исходный код шейдера из filePath

    ifstream shaderFile;

    cout << shaderPath << endl;

    // Удостоверимся, что ifstream объекты могут выкидывать исключения
    shaderFile.exceptions(ifstream::badbit);

    string res;

    try {
        // Открываем файлы
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;

        // Считываем данные в потоки
        shaderStream << shaderFile.rdbuf();

        // Закрываем файлы
        shaderFile.close();

        // Преобразовываем потоки в массив GLchar
        res = shaderStream.str();

    } catch (ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    return string(res);//IMPORTANT RETURN BY VALUE!!!
}


void Graphic::registerShader(GLuint &shaderProgram, const string &vertexPath, const string &fragmentPath) {

    registerOneShader(shaderProgram, GL_VERTEX_SHADER, loadGLSL(vertexPath));
    registerOneShader(shaderProgram, GL_FRAGMENT_SHADER, loadGLSL(fragmentPath));
}

