// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>


#include <GLFW/glfw3.h>

#include <iostream>


GLFWwindow* window; 

int main() {

    // Инициализируем GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Ошибка при инициализации GLFWn" );
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// Открыть окно и создать в нем контекст OpenGL
    window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Невозможно открыть окно GLFW. Если у вас Intel GPU, то он не поддерживает версию 3.3. Попробуйте версию уроков для OpenGL 2.1.n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    // Включим режим отслеживания нажатия клавиш, для проверки ниже
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do{
        // Пока что ничего не выводим. Это будет в уроке 2.

        // Сбрасываем буферы
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Проверяем нажатие клавиши Escape или закрытие окна
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );
    return 0;
}
