//
// Created by NickNovikov on 10.06.2018.
//

#ifndef LESSONS_SCENE_H
#define LESSONS_SCENE_H

#include <list>
#include <vector>
#include <string>
#include <set>
#include <map>
#include "Model.h"
#include "GameObject.h"

namespace Graphic {//todo serialize to json
    class Scene {
    private:
        std::set<std::vector<int>> coords;
        std::map<std::string, std::shared_ptr<Model>> models;
        std::list<std::shared_ptr<GameObject>> objects;
        std::list<std::shared_ptr<Light>> lights;
    public:

        Scene(const std::string &filepath);

        virtual ~Scene();

        void render(Camera &camera, const float &step);
    };
}


#endif //LESSONS_SCENE_H
