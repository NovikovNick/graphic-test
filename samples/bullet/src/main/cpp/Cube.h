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

#include <btBulletDynamicsCommon.h>

namespace Graphic {

    class Cube {
    private:
        GLuint VAO, VBO, texture;
        float side;
        glm::vec3 position;

        btCollisionShape* ptrShape;
        btRigidBody* ptrRigidBody;
        btDefaultMotionState* ptrMotionState;

    public:

        btCollisionShape *getGroundShape() const;

        btRigidBody *getBody() const;

        Cube(const float &side, const int &x, const int &y, const int &z, const float &mass);

        virtual ~Cube();

        void translate(const glm::vec3 &translate);

        void render(const GLuint &shaderProgram);

        void setTexture(const GLuint &texture);
    };

    GLuint loadTexture(const std::string &filepath);
}

#endif //LESSONS_CUBE_H
