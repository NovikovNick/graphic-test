//
// Created by NickNovikov on 05.06.2018.
//

#ifndef LESSONS_CUBE_H
#define LESSONS_CUBE_H

// GL Includes
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"
#include "Camera.h"

namespace Graphic {
    class Cube : public Model {
    private:
        float side;
        GLuint specularTexture;
    public:

        Cube(GLuint &shaderProgram, GLuint &texture, float side = 1);

        void render(Camera &camera, std::list<std::shared_ptr<Light>> lights, glm::vec3 position);
    };
}


#endif //LESSONS_CUBE_H
