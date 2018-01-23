#include <iostream>
#include "Field/Field.h"
#include "Game/Game.h"

int main() {
    // Exemple file path textFiles/text.txt
    std::cout << "Write path to initialize file" << std::endl;
    std::string path;
    std::cin>>path;
    Game game;
    game.setFilePath(path);
    game.start();
    return 0;
}