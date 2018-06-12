//
// Created by NickNovikov on 07.06.2018.
//
#include "Model.h"
#include "Camera.h"
#include "GameObject.h"
#include "Light.h"

Graphic::GameObject::GameObject(std::shared_ptr<Graphic::Model> ptrModel, glm::vec3 position, const float &side, const float &m)
        : ptrModel(ptrModel), position(position) {}

void Graphic::GameObject::render(Camera &camera, std::list<std::shared_ptr<Light>> lights) {

    this->ptrModel.get()->render(camera, position);
};