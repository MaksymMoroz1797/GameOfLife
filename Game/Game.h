//
// Created by Moroz on 23.01.2018.
//

#ifndef GAMEOFLIFE_1_GAME_H
#define GAMEOFLIFE_1_GAME_H
#include "../Field/Field.h"
#include "../Field/FieldBuilder.h"
#include <fstream>
#include <string>

class Game {
public:
    Game();

    void setFilePath(const std::string &filePath);

    void start();

private:
    std::string filePath;
    Field * field;
};

#endif //GAMEOFLIFE_1_GAME_H
