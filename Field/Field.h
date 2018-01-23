//
// Created by Moroz on 21.01.2018.
//

#ifndef GAMEOFLIFE_1_FIELD_H
#define GAMEOFLIFE_1_FIELD_H
#include <vector>
#include <mutex>
#include "../ThreadPool/ThreadPool.h"

using std::vector;

class Field {
public:
    Field(const std::vector < vector <bool> > & initMattrix_, int xSize_, int ySize_, int threadsNumber_);
    ~Field();
    bool getStageOfCell(int x, int y) const;
    void calculateNextField();
    bool getNextStageOfCell(int x, int y);

    int getXSize() const;

    int getYSize() const;

private:
    bool validCoordinates(int x, int y) const;
    const int xSize;
    const int ySize;
    const int threadsNumber;
    volatile bool * * fieldMatrix;
    volatile bool * * additionalFieldMatrix;
    ThreadPool pool;
};

void consoleFieldPrint(const Field & field);

#endif //GAMEOFLIFE_1_FIELD_H
