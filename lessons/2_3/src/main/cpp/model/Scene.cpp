//
// Created by NickNovikov on 10.06.2018.
//



#include <iostream>
#include <fstream>
#include <sstream>

#include "Scene.h"
#include "Util.h"
#include "Cube.h"

void generate(std::set<std::vector<int>> &coord);

void load(const std::string &filepath, std::set<std::vector<int>> &coord);

void save(const std::string &filepath, std::set<std::vector<int>> &coord);

void initModels(std::map<std::string, std::shared_ptr<Graphic::Model>> &models);

Graphic::Scene::Scene(const std::string &filepath) {

    using namespace std;

    load(filepath, coords);

    initModels(models);

    for (auto coord : coords) {//create cubes
        Graphic::GameObject cube(models.at("cube"), glm::vec3(coord[0], coord[1], coord[2]), 1.0f, 0.0f);
        shared_ptr<Graphic::GameObject> ptrCube = make_shared<Graphic::GameObject>(cube);
        objects.push_back(ptrCube);
    };
    {//create lights
        Graphic::Light light = Graphic::Light();
        light.color = glm::vec3(1., 1., 1.);
        light.position = glm::vec3(0., 2., 0.);
        shared_ptr<Graphic::Light> ptrLight = make_shared<Graphic::Light>(light);
        lights.push_back(ptrLight);
    }
}

void Graphic::Scene::render(Camera &camera, const float &step) {
    for (auto light : lights) {
        light.get()->render(camera);
        light.get()->position = glm::vec3(0, 6, cos(step)*10);
        light.get()->color = glm::vec3(sin(step)*0.5f, 0.5f, 0.5f);
    }
    for (auto obj : objects) obj.get()->render(camera, lights);
}

Graphic::Scene::~Scene() {
    models.clear();
    lights.clear();
    objects.clear();
}

//COMVENIENCE

void initModels(std::map<std::string, std::shared_ptr<Graphic::Model>> &models){

    using namespace std;

    GLuint simpleShader = glCreateProgram();
    Graphic::registerShader(simpleShader,
                            "..\\lessons\\2_3\\src\\main\\glsl\\model\\cube\\shader.vs.glsl",
                            "..\\lessons\\2_3\\src\\main\\glsl\\model\\cube\\shader.frag.glsl"
    );

    GLuint lightShader = glCreateProgram();
    Graphic::registerShader(lightShader,
                            "..\\lessons\\2_3\\src\\main\\glsl\\model\\light\\shader.vs.glsl",
                            "..\\lessons\\2_3\\src\\main\\glsl\\model\\light\\shader.frag.glsl"
    );

    GLuint simpleCubeTexture = Graphic::loadTexture("..\\assets\\cube.jpg");

    models["light"] = make_shared<Graphic::Cube>(Graphic::Cube(lightShader, simpleCubeTexture, 0.5f));
    models["cube"] = make_shared<Graphic::Cube>(Graphic::Cube(simpleShader, simpleCubeTexture, 1));

};

void load(const std::string &filepath, std::set<std::vector<int>> &coord) {
    using namespace std;
    try {
        ifstream coordFile;
        coordFile.exceptions(ifstream::badbit);
        coordFile.open(filepath);
        //coord = std::vector <std::vector<int>>();

        string line;
        while (std::getline(coordFile, line)) {
            vector<int> tokens;
            string token;
            istringstream tokenStream(line);
            while (std::getline(tokenStream, token, ';')) {
                tokens.push_back(stoi(token));

            }

            coord.insert(vector<int>(tokens));
        }
        coordFile.close();

    } catch (ifstream::failure e) {
        cout << "ERROR::COORD::FILE_NOT_SUCCESFULLY_READ" << endl;
    }
};

void save(const std::string &filepath, std::set<std::vector<int>> &coord) {
    using namespace std;
    try {
        ofstream coordFile;
        coordFile.exceptions(ifstream::badbit);
        coordFile.open(filepath);

        for (auto c : coord) coordFile << c[0] << ";" << c[1] << ";" << c[2] << endl;

        coordFile.close();

    } catch (ifstream::failure e) {
        cout << "ERROR::COORD::FILE_NOT_SUCCESFULLY_READ" << endl;
    }
};

void generate(std::set<std::vector<int>> &coord) {

    using namespace std;

    for (int sign = -1; sign < 2; sign += 2) {
        for (int z = -20; z <= 20; ++z) {

            for (int i = -12; i <= 0; ++i) coord.insert(vector<int>{i * sign, 0, z});
            for (int i = 1; i <= 5; ++i) coord.insert(vector<int>{-12 * sign, i, z});

            coord.insert(vector<int>{-11 * sign, 6, z});
            coord.insert(vector<int>{-10 * sign, 7, z});
            coord.insert(vector<int>{-9 * sign, 8, z});
            coord.insert(vector<int>{-8 * sign, 9, z});
            coord.insert(vector<int>{-7 * sign, 10, z});
            coord.insert(vector<int>{-6 * sign, 10, z});
            coord.insert(vector<int>{-5 * sign, 10, z});
            if (z == 12 || z == -12) {
                for (int column = 0; column < 12; ++column) coord.insert(vector<int>{-4 * sign, column, z});
            } else {
                coord.insert(vector<int>{-4 * sign, 11, z});
            }
            coord.insert(vector<int>{-3 * sign, 11, z});
            coord.insert(vector<int>{-2 * sign, 11, z});
        }

        int length = 8;
        for (int x = -12; x <= 12; ++x) {
            for (int i = -12; i <= 0; ++i) coord.insert(vector<int>{x, 0, (i - length) * sign});
            for (int i = 1; i <= 5; ++i) coord.insert(vector<int>{x, i, (-12 - length) * sign});
            coord.insert(vector<int>{x, 6, (-11 - length) * sign});
            coord.insert(vector<int>{x, 7, (-10 - length) * sign});
            coord.insert(vector<int>{x, 8, (-9 - length) * sign});
            coord.insert(vector<int>{x, 9, (-8 - length) * sign});
            coord.insert(vector<int>{x, 10, (-7 - length) * sign});
            coord.insert(vector<int>{x, 10, (-6 - length) * sign});
            coord.insert(vector<int>{x, 10, (-5 - length) * sign});
            coord.insert(vector<int>{x, 11, (-4 - length) * sign});
            coord.insert(vector<int>{x, 11, (-3 - length) * sign});
            coord.insert(vector<int>{x, 11, (-2 - length) * sign});
        }
    }
}