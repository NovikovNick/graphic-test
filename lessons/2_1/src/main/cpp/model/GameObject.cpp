//
// Created by NickNovikov on 07.06.2018.
//

#include "GameObject.h"
#include "Model.h"
#include "Camera.h"


Graphic::GameObject::GameObject(Model &model, glm::vec3 position, const float &side, const float &m) : model(model), position(position){

    btScalar s = btScalar(side / 2)+0.001f;
    ptrShape = new btBoxShape(btVector3(s, s, s));

    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(position.x, position.y, position.z));

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


void Graphic::GameObject::translate(const glm::vec3 &translate) {
    position = translate;
}

void Graphic::GameObject::render(Camera &camera){

    if (ptrRigidBody && ptrRigidBody->getMotionState()){

        btRigidBody* body = btRigidBody::upcast(ptrRigidBody);
        btTransform trans;
        body->getMotionState()->getWorldTransform(trans);
        this->translate(glm::vec3(float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ())));
    }
   model.render(camera, position);
};