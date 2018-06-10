//
// Created by NickNovikov on 10.06.2018.
//

#ifndef LESSONS_SCENE_H
#define LESSONS_SCENE_H

#include <list>
#include <vector>
#include <string>
#include <set>

namespace Graphic {
    class Scene {
    private:
        std::set<std::vector<int>> coord;
    public:

        Scene(const std::string &filepath);

        std::set<std::vector<int>> getCoord();
    };
}


#endif //LESSONS_SCENE_H
