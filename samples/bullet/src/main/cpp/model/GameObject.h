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
#include "Cube.h"

namespace Graphic {
    class GameObject {
    private:
        Cube &model;
        glm::vec3 position;
        btBoxShape* ptrShape;
        btDefaultMotionState *ptrMotionState;
    public:
        btRigidBody *ptrRigidBody;
        GameObject(Cube &model, glm::vec3 position, const float &side, const float &mass);
        void translate(const glm::vec3 &translate);
        void render(Camera &camera);
    };
}


#endif //LESSONS_GAMEOBJECT_H
