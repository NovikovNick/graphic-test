//
// Created by NickNovikov on 05.06.2018.
//

#ifndef LESSONS_MODEL_H
#define LESSONS_MODEL_H

// GL Includes
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Graphic {


    class Model {
    public:
        GLuint VAO, VBO, shaderProgram, texture;
    };
}

#endif //LESSONS_MODEL_H
