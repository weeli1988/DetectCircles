#pragma once

#include "Helper.h"
#include <cmath>

int calculateDistance(int x1, int y1, int x2, int y2) {
    return std::sqrt(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2));
}
