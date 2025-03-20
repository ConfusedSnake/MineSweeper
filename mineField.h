#pragma once
#include <vector>
#include <random>
#include <ostream>
#include <memory>  

class Field {
private:
    const int fieldW = 30;
    const int fieldH = 16;
    const int amountBombs = 99;

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

    void plantBombs(std::vector<std::unique_ptr<std::vector<int>>>& fieldVec);

    Field();
};

std::ostream& operator<<(std::ostream& os, const Field& field);
