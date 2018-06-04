//
// Created by NickNovikov on 03.06.2018.
//
#include "Cube.h"

Graphic::Cube::Cube(const float &side, const int &x, const int &y, const int &z, const float &m)
        : side(side),
          position(glm::vec3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)))  {


    //texture = Graphic::loadTexture("..\\assets\\cube.jpg");

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    GLfloat vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// 3. Устанавливаем указатели на вершинные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT,GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)




    {
        btScalar s = btScalar(side / 2);
        ptrShape = new btBoxShape(btVector3(s, s, s));

        btTransform groundTransform;
        groundTransform.setIdentity();
        groundTransform.setOrigin(btVector3(x, y, z));

        btScalar mass(m);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            ptrShape->calculateLocalInertia(mass, localInertia);

        //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects

        ptrMotionState = new btDefaultMotionState(groundTransform);

        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, ptrMotionState, ptrShape, localInertia);
        ptrRigidBody = new btRigidBody(rbInfo);
    }

}

void Graphic::Cube::translate(const glm::vec3 &translate) {
    position = translate;
}

void Graphic::Cube::render(const GLuint &shaderProgram) {

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);

    glBindVertexArray(VAO);
    glm::mat4 model;
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(side, side, side));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

Graphic::Cube::~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    delete ptrShape;
    delete ptrMotionState;
    delete ptrRigidBody;
}

void Graphic::Cube::setTexture(const GLuint &refTexture){
    texture = refTexture;
}

btCollisionShape *Graphic::Cube::getGroundShape() const {
    return ptrShape;
}

btRigidBody *Graphic::Cube::getBody() const {
    return ptrRigidBody;
}
