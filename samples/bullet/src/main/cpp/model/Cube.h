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
    class Cube : protected Model {
    private:
        float side;
    public:
        Cube(float side = 1);
        void render(Camera &camera, glm::vec3 position);
    };
}


#endif //LESSONS_CUBE_H
