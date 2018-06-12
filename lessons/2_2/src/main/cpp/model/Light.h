//
// Created by NickNovikov on 12.06.2018.
//

#ifndef LESSONS_LIGHT_H
#define LESSONS_LIGHT_H

#include <glm/glm.hpp>
#include <memory>
#include "Model.h"

namespace Graphic {
    class Light {
    public:
        std::shared_ptr<Model> ptrModel;
        glm::vec3 position;
        void render(Camera &camera);
    };
}


#endif //LESSONS_LIGHT_H
