//
// Created by NickNovikov on 10.06.2018.
//

#include "Scene.h"

#include <iostream>
#include <fstream>
#include <sstream>


std::set<std::vector<int>> Graphic::Scene::getCoord() {
    return coord;
}

void generate(std::set<std::vector<int>> &coord);

void load(const std::string &filepath, std::set<std::vector<int>> &coord);

void save(const std::string &filepath, std::set<std::vector<int>> &coord);

Graphic::Scene::Scene(const std::string &filepath) {

    load(filepath, coord);

}

//COMVENIENCE

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