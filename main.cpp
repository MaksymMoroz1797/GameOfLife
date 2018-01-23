#include <iostream>
#include "Field/Field.h"
#include "Game/Game.h"


int main() {
    // Exemple file path textFiles/text.txt
    std::cout << "Write path to initialize file, Exemple file : textFiles/text.txt.\n"
            "File Format: first and second parameters are grid dimension, "
            "third is thread number, next is grid " << std::endl;
    std::string path;
    std::cin>>path;
    Game game;
    game.setFilePath(path);
    game.start();
    return 0;
}