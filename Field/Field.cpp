//
// Created by Moroz on 22.01.2018.
//
#include "Field.h"
//#include "Barrier .h"
#include <thread>
#include <stdexcept>
#include <fstream>
#include <string>
#include <iostream>

using std::thread;


Field::Field(const std::vector < vector <bool> > & initMattrix_, int xSize_, int ySize_, int threadsNumber_):
        xSize(xSize_),
        ySize(ySize_),
        threadsNumber(threadsNumber_) {
    fieldMatrix = new volatile bool*[xSize];
    additionalFieldMatrix = new volatile bool *[ySize];
    for (int i = 0; i < xSize; ++i) {
        fieldMatrix[i] = new volatile bool[ySize];
        additionalFieldMatrix[i] = new volatile bool[ySize];
        for (int j = 0; j < ySize; ++j) {
            fieldMatrix[i][j] = initMattrix_[i][j];
        }
    }
}

Field::~Field() {
    for (int i = 0; i < xSize; ++i) {
        delete[] fieldMatrix[i];
        delete[] additionalFieldMatrix[i];
    }
    delete[] fieldMatrix;
    delete[] additionalFieldMatrix;
}

bool Field::validCoordinates(int x, int y) const {
    return  x < this->xSize && x >= 0 &&
            y < this->ySize && y >= 0;
}

bool Field::getStageOfCell(int x, int y) const {
    if (validCoordinates(x, y)) {
        return this->fieldMatrix[x][y];
    } else {
        throw new std::invalid_argument("Incorrect coordinates of field");
    }
}

bool Field::getNextStageOfCell(int x, int y) {
    int numOfAliveNeighbors = 0;
    auto addAliveCell = [&](int x_, int y_) {
        if (this->validCoordinates(x_, y_)) {
            numOfAliveNeighbors += this->getStageOfCell(x_, y_);
    }};
    addAliveCell(x - 1, y - 1);
    addAliveCell(x - 1, y);
    addAliveCell(x - 1, y + 1);
    addAliveCell(x, y + 1);
    addAliveCell(x + 1, y + 1);
    addAliveCell(x + 1, y);
    addAliveCell(x + 1, y - 1);
    addAliveCell(x, y - 1);
    bool currentStage = this->getStageOfCell(x, y);
    if (numOfAliveNeighbors < 2) {
        return false;
    } if (numOfAliveNeighbors == 2) {
        return currentStage;
    } if (numOfAliveNeighbors == 3) {
        return true;
    } else {
        return false;
    }
}

void Field::calculateNextField() {
    auto fieldCalcInRange = [&](int xLim, int yLim) {
        for (int i = xLim; i < yLim; ++i) {
            for (int j = 0; j < ySize; ++j) {
                additionalFieldMatrix[i][j] = this->getNextStageOfCell(i, j);
            }
        }
    };
    vector<std::thread *> threads(0);
    int part = xSize / threadsNumber;
    for (int i = 0; i < threadsNumber; ++i) {
        int leftLim = part * i;
        int rightLim = i != threadsNumber - 1 ? part * (i + 1) : xSize;
        if (leftLim != rightLim) {
            threads.push_back(new thread(fieldCalcInRange, leftLim, rightLim));
        }
    }
    for (thread * thr : threads) {
        thr->join();
    }
    volatile bool * * tmp = this->fieldMatrix;
    this->fieldMatrix = this->additionalFieldMatrix;
    this->additionalFieldMatrix = tmp;
}

void consoleFieldPrint(const Field & field) {
    for (int i = 0; i < field.getXSize(); ++i) {
        for (int j = 0; j < field.getYSize(); ++j) {
            std::cout << field.getStageOfCell(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


int Field::getXSize() const {
    return xSize;
}

int Field::getYSize() const {
    return ySize;
}


