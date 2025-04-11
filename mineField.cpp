#include "mineField.h"
#include <iostream>

Field::Field(const int fieldW, const int fieldH, int x, int y, bool load) : fieldW(fieldW), fieldH(fieldH), x(x), y(y) {
    fieldVec.reserve(fieldH);

    for (int i = 0; i < fieldH; i++) {
        fieldVec.push_back(std::make_unique<std::vector<int>>(fieldW, 0));
    }

    if (!load){
        plantBombs();
    }

    dx = (x > 0 && x < fieldW - 1) ? 1 : 0;
    dy = (y > 0 && y < fieldH - 1) ? 1 : 0;
}

void Field::plantBombs(){
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distributionH(0, fieldH - 1);
    std::uniform_int_distribution<int> distributionW(0, fieldW - 1);

    int indexH = distributionH(generator);
    int indexW = distributionW(generator);

    for (int i = 0; i < amountBombs; i++) {
        
        do{
            indexH = distributionH(generator);
            indexW = distributionW(generator);
        } while(
            indexW >= (x-dx) && indexW <= (x+dx) &&
            indexH >= (y-dy) && indexH <= (y+dy)
        );

        while (1){
            if (((*fieldVec[indexH])[indexW] != -1)){
                break;
            } else {
                do{
                    indexH = distributionH(generator);
                    indexW = distributionW(generator);
                } while(
                    indexW >= (x-dx) && indexW <= (x+dx) &&
                    indexH >= (y-dy) && indexH <= (y+dy)
        );
            }
        }

        for (int dh = -1; dh <= 1; ++dh) {
            for (int dw = -1; dw <= 1; ++dw) {
                if (dh == 0 && dw == 0){
                    (*fieldVec[indexH])[indexW] = -1;
                    continue;
                }

                int newH = indexH + dh;
                int newW = indexW + dw;

                if (newH >= 0 && newH < fieldH && newW >= 0 && newW < fieldW) {
                    if ((*fieldVec[newH])[newW] != -1) {
                        (*fieldVec[newH])[newW] += 1;
                    }
                }
            }
        } 
    }
}

void Field::changeFieldVec(int y, int x, int value){
    fieldVec.at(y)->at(x) = value;
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
