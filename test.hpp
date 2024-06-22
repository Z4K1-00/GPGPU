#ifndef __TEST_HPP__
#define __TEST_HPP__

#include "utils/ppm.hpp"
#include "utils/commonCUDA.hpp"
#include "cmath"
#include <iostream>
#include <vector>

struct Point
{
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator!=(const Point &other) const {
        return x != other.x || y != other.y;
    }
};

void DDA(const Point &A, const Point &B, std::vector<Point> &pixelsRasterisation);
float naive_viewtestCPU(const los::Heightmap &hm, const Point &c, los::Heightmap &resultatsCPU);

#endif