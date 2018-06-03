//
// Created by NickNovikov on 03.06.2018.
//

#ifndef LESSONS_CUBE_H
#define LESSONS_CUBE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace Graphic {

    class Cube {
    private:
        GLuint VAO, VBO, texture, side;
        glm::vec3 position;
    public:
        Cube(const int &side, const int &x, const int &y, const int &z);

        virtual ~Cube();

        void translate(const glm::vec3 &translate);

        void render(const GLuint &shaderProgram);
    };

    GLuint loadTexture(const std::string &filepath);
}

#endif //LESSONS_CUBE_H
