#ifndef __REFERENCE_HPP__
#define __REFERENCE_HPP__

#include "utils/ppm.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

struct Point {
    int x, y, z;
    Point(int x, int y, int z) : x(x), y(y), z(z) {}
};

double calculateAngle(const Point& a, const Point& b);
std::vector<Point> performDDA(const Point& start, const Point& end);
float naive_viewtestCPU(const los::Heightmap &in, los::Heightmap &out);

#endif // __REFERENCE_HPP__
