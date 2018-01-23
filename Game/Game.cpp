//
// Created by Moroz on 23.01.2018.
//

#include "Game.h"
#include <thread>

void Game::setFilePath(const std::string &filePath) {
    Game::filePath = filePath;
    field = &readFieldFromFile(filePath);
    if (field == nullptr) {
        throw new std::invalid_argument("Incorrect file path");
    }
}

Game::Game() {

}

void Game::start() {
    if (field == nullptr) {
        throw new std::invalid_argument("Not initialize");
    }
    while (true) {
        consoleFieldPrint(*field);
        field->calculateNextField();
        std::this_thread::sleep_for (std::chrono::seconds(2));
    }
}
