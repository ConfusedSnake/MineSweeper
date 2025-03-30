#pragma once
#include <vector>
#include <random>
#include <ostream>
#include <memory>  

class Field {
private:
    const int fieldW;
    const int fieldH;
    int x;
    int y;
    int dx = 1;
    int dy = 1;
    const int amountBombs = 70;

    std::vector<std::unique_ptr<std::vector<int>>> fieldVec;

public:
    const std::vector<std::unique_ptr<std::vector<int>>>& getField() const {
        return fieldVec;
    }

    const int getW() const{
        return fieldW;
    }

    const int getH() const{
        return fieldH;
    }

    const int getBombs() const{
        return amountBombs;
    }

    void plantBombs();

    Field(const int fieldW, const int fieldH, int x, int y, bool load);

    void changeFieldVec(int y, int x, int value);
};

std::ostream& operator<<(std::ostream& os, const Field& field);
