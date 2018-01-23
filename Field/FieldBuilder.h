//
// Created by Moroz on 23.01.2018.
//

#ifndef GAMEOFLIFE_1_FIELDBUILDER_H
#define GAMEOFLIFE_1_FIELDBUILDER_H

#include "Field.h"

class FieldBuilder {
public:
    FieldBuilder(int xDim_, int yDim_, int threadNum_);
    void set(int x, int y, bool val);
    bool nextSet(bool val);
    Field & getField();
    const int getXDim() const;
    const int getYDim() const;

private:
    std::vector < vector <bool> > field;
    const int xDim;
    const int yDim;
    const int threadNum;
    int currentInitCell;
};

Field & readFieldFromFile(const std::string & path);

#endif //GAMEOFLIFE_1_FIELDBUILDER_H
