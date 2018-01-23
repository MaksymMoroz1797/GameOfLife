//
// Created by Moroz on 23.01.2018.
//
#include "FieldBuilder.h"
#include <fstream>
#include <string>
#include <iostream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
using std::string;

FieldBuilder::FieldBuilder(int xDim_, int yDim_, int threadNum_): xDim(xDim_), yDim(yDim_),
                                                                  threadNum(threadNum_),
                                                                  currentInitCell(0),
                                                                  field(xDim_, vector<bool>(yDim_)) { }

void FieldBuilder::set(int x, int y, bool val) {
    if (x < this->xDim && x >= 0 &&
    y < this->yDim && y >= 0) {
        field[x][y] = val;
    } else {
        throw new std::invalid_argument("Incorrect coordinates of field");
    }
}

Field & FieldBuilder::getField() {
    return * new Field(field, xDim, yDim,threadNum);
}

bool FieldBuilder::nextSet(bool val) {
    if (currentInitCell <= xDim * yDim) {
        set(currentInitCell / xDim, currentInitCell % yDim, val);
        ++currentInitCell;
        return true;
    } else return false;
}

const int FieldBuilder::getXDim() const {
    return xDim;
}

const int FieldBuilder::getYDim() const {
    return yDim;
}

Field & readFieldFromFile(const std::string & path) {
    std::vector<double> xvector;
    std::ifstream infile(path);
    if ( ! infile ) {
        std::cout << "Error in opening file !" << std::endl;
        throw new std::invalid_argument("Incorrect file path");
    }
    string str;
    string resString;
    while (std::getline(infile, str)) {
        resString +=str + " ";
    }
    std::istringstream iss(resString);
    vector<string> tokens;
    copy(std::istream_iterator<string>(iss),
         std::istream_iterator<string>(),
         back_inserter(tokens));
    const int xDim = atoi(tokens.at(0).c_str());
    const int yDim = atoi(tokens.at(1).c_str());
    const int threadsNum = atoi(tokens.at(2).c_str());
    FieldBuilder fieldBuilder(xDim, yDim, threadsNum);
    for (int i = 3; i < tokens.size(); ++i) {
        bool val = (bool) atoi(tokens.at(i).c_str());
        fieldBuilder.nextSet(val);
    }

    return fieldBuilder.getField();
}
