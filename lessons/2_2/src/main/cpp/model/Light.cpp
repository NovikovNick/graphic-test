//
// Created by NickNovikov on 12.06.2018.
//

#include "Light.h"

void Graphic::Light::render(Camera &camera) {

    if(this->ptrModel){
        this->ptrModel.get()->render(camera, position);
    }
};