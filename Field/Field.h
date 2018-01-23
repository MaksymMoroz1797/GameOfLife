//
// Created by Moroz on 21.01.2018.
//
#include <vector>
#include <mutex>

#ifndef GAMEOFLIFE_1_FIELD_H
#define GAMEOFLIFE_1_FIELD_H

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
};

void consoleFieldPrint(const Field & field);

#endif //GAMEOFLIFE_1_FIELD_H
