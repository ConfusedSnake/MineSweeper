#include "mineField.h"
#include <iostream>

Field::Field() {
    fieldVec.reserve(fieldH);

    for (int i = 0; i < fieldH; i++) {
        fieldVec.push_back(std::make_unique<std::vector<int>>(fieldW, 0));
    }

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distributionH(0, fieldH - 1);
    std::uniform_int_distribution<int> distributionW(0, fieldW - 1);

    for (int i = 0; i < amountBombs; i++) {
        while (1){
            int indexH = distributionH(generator);
            int indexW = distributionW(generator);

            if ((*fieldVec[indexH])[indexW] != -1){
                (*fieldVec[indexH])[indexW] = -1; 
                break;
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Field& field) {
    for (const auto& row : field.getField()) {
        for (int val : *row) {
            os << val << " ";
        }
        os << std::endl;
    }
    return os;
}

/*
try
                {
                    (*fieldVec[indexH+1])[indexW] += 1;
                    (*fieldVec[indexH+1])[indexW-1] += 1;
                    (*fieldVec[indexH+1])[indexW+1] += 1;

                    (*fieldVec[indexH-1])[indexW] += 1;
                    (*fieldVec[indexH-1])[indexW+1] += 1;
                    (*fieldVec[indexH-1])[indexW-1] += 1;
                
                    (*fieldVec[indexH])[indexW-1] += 1;
                    (*fieldVec[indexH])[indexW+1] += 1;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
*/