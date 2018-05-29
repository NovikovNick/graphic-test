#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Graphic.h"

GLFWwindow *window;
bool isWireFrameState = false;

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
                                   "layout (location = 0) in vec3 position;\n"
                                   "layout (location = 1) in vec3 color;\n"
                                   "out vec3 ourColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "gl_Position = vec4(position, 1.0);\n"
                                   "ourColor = color;\n"
                                   "}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
                                     "out vec4 color;\n"
                                     "in vec3 ourColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "color = vec4(ourColor, 1.0f);\n"
                                     "}\n\0";

//it is better to use GL primitive type instead predefined
const GLuint WIDTH = 1024, HEIGHT = 768;

void handleESC(GLFWwindow *window, int key, int scancode, int action, int mode);

void handleWireSwitch(GLFWwindow *window, int key, int scancode, int action, int mode);


int main() {

    window = Graphic::initGLFW(WIDTH, HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, handleESC);
    glfwSetKeyCallback(window, handleWireSwitch);


    Graphic::initGLAD();


    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;


    GLuint shaderProgram = glCreateProgram();
    Graphic::registerShader(
            shaderProgram,
            "C:\\WORK\\WORKSPASE\\CPP\\fst-steps\\lessons\\1_5\\src\\main\\glsl\\shader.vs.glsl",
            "C:\\WORK\\WORKSPASE\\CPP\\fst-steps\\lessons\\1_5\\src\\main\\glsl\\shader.frag.glsl"
    );

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    GLfloat vertices[] = {
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// Верхний угол
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Нижний правый угол
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // Нижний левый угол
    };

    //create vertex buffer object and vertex array object
    GLuint VBO, VAO;//, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &EBO);

// 1. Привязываем VAO
    glBindVertexArray(VAO);
// 2. Копируем наш массив вершин в буфер для OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 3. Копируем наши индексы в в буфер для OpenGL
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

// 3. Устанавливаем указатели на вершинные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);   // Note that this is allowed, the call to glVertexAttribPointer registered VBO
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

        GLfloat timeValue = glfwGetTime();
        GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
        GLfloat redValue = (sin(timeValue) / 3) + 0.5;
        GLfloat blueValue = (sin(timeValue) / 4) + 0.5;
        //GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUseProgram(shaderProgram);
        //glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);


        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

