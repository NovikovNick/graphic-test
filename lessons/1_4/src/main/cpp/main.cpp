#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

GLFWwindow *window;
bool isWireFrameState = false;

// Shaders
const GLchar *vertexShaderSource = "#version 330 core\n"
                                   "layout (location = 0) in vec3 position;\n"
                                   "void main()\n"
                                   "{\n"
                                   "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
                                   "}\0";
const GLchar *fragmentShaderSource = "#version 330 core\n"
                                     "out vec4 color;\n"
                                     "void main()\n"
                                     "{\n"
                                     "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                     "}\n\0";

//it is better to use GL primitive type instead predefined
const GLuint WIDTH = 1024, HEIGHT = 768;

void handleESC(GLFWwindow *window, int key, int scancode, int action, int mode);

void handleWireSwitch(GLFWwindow *window, int key, int scancode, int action, int mode);

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

    GLFWwindow *initGLFW() {
        glfwInit();
        // Set all the required options for GLFW
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//avoid old function
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        // Create a GLFWwindow object that we can use for GLFW's functions
        GLFWwindow *window_ptr = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
        if (window_ptr == nullptr) {
            throw Init_GLFW_Error("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(window_ptr);

        return window_ptr;
    }

    void initGLAD() {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            throw Init_GLAD_Error("Failed to initialize OpenGL context");
        }
    }

    void registerShader(GLuint &shaderProgram, GLenum shaderType, const GLchar **shader_src) {
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, shader_src, NULL);
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
}

int main() {

    window = Graphic::initGLFW();

    // Set the required callback functions
    glfwSetKeyCallback(window, handleESC);
    glfwSetKeyCallback(window, handleWireSwitch);


    Graphic::initGLAD();


    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);


    GLuint shaderProgram = glCreateProgram();

    Graphic::registerShader(shaderProgram, GL_VERTEX_SHADER, &vertexShaderSource);
    Graphic::registerShader(shaderProgram, GL_FRAGMENT_SHADER, &fragmentShaderSource);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    GLfloat vertices[] = {
            0.5f, 0.5f, 0.0f,  // Верхний правый угол
            0.5f, -0.5f, 0.0f,  // Нижний правый угол
            -0.5f, -0.5f, 0.0f,  // Нижний левый угол
            -0.5f, 0.5f, 0.0f   // Верхний левый угол
    };
    GLuint indices[] = {  // Помните, что мы начинаем с 0!
            0, 1, 3,   // Первый треугольник
            1, 2, 3    // Второй треугольник
    };

    //create vertex buffer object and vertex array object
    GLuint VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

// 1. Привязываем VAO
    glBindVertexArray(VAO);
// 2. Копируем наш массив вершин в буфер для OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 3. Копируем наши индексы в в буфер для OpenGL
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

// 3. Устанавливаем указатели на вершинные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   // Note that this is allowed, the call to glVertexAttribPointer registered VBO
    // as the currently bound vertex buffer object so afterwards we can safely
    // unbind

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        /*glDrawArrays(GL_TRIANGLES, 0, 3);*/
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Terminates GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

void handleESC(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void handleWireSwitch(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
        if (isWireFrameState) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        isWireFrameState = !isWireFrameState;
    }
}

