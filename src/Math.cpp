
#include "Math.h"


float randomFloat() {
    return ((float) (std::rand() % 1000)) / (float) 1000;
}



Int randomIntBetween(const Int & min, const Int & max) {
    int a = std::min(min, max);
    int b = std::max(min, max);
    int c = b - a;
    return std::rand() % c + a;
}

float randomFloatBetween(const Int & min, const Int & max) {
    Int a = std::min(min, max);
    Int b = std::max(min, max);
    Int c = b - a;
    return std::rand() % c + a;
}