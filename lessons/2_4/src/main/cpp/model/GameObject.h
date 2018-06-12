//
// Created by NickNovikov on 07.06.2018.
//

#ifndef LESSONS_GAMEOBJECT_H
#define LESSONS_GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <btBulletDynamicsCommon.h>
#include <list>
#include "Model.h"
#include "Light.h"

namespace Graphic {
    class GameObject {
    private:

        std::shared_ptr<Model> ptrModel;

    public:

        glm::vec3 position;

        GameObject(std::shared_ptr<Model> ptrModel, glm::vec3 position, const float &side, const float &mass);

        void render(Camera &camera, std::list<std::shared_ptr<Light>> lights);
    };
}


#endif //LESSONS_GAMEOBJECT_H
