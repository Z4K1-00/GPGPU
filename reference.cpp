#include "reference.hpp"
#include "utils/chronoCPU.hpp"
#include <iostream>
#include <cmath>

double calculateAngle(const Point& a, const Point& b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double dz = b.z - a.z;
    return atan2(dz, sqrt(dx * dx + dy * dy));
}

std::vector<Point> performDDA(const Point& start, const Point& end) {
    std::vector<Point> points;

    int dx = end.x - start.x;
    int dy = end.y - start.y;
    int dz = end.z - start.z;

    int D = std::max(std::abs(dx), std::abs(dy));
    double stepx = static_cast<double>(dx) / D;
    double stepy = static_cast<double>(dy) / D;
    double stepz = static_cast<double>(dz) / D;

    double x = start.x;
    double y = start.y;
    double z = start.z;

    for (int i = 0; i <= D; ++i) {
        points.emplace_back(std::round(x), std::round(y), std::round(z));
        x += stepx;
        y += stepy;
        z += stepz;
    }

    return points;
}

float naive_viewtestCPU(const los::Heightmap &in, los::Heightmap &out) {
    const int width = in.getWidth();
    const int height = in.getHeight();

    int centerX = 245;
    int centerY = 497;
    
    int centerZ = in.getPixel(centerX, centerY);
    Point center(centerX, centerY, centerZ);

    std::vector<std::vector<bool>> visibility(height, std::vector<bool>(width, false));

    ChronoCPU chr;
    chr.start();
    
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            if (i == center.x && j == center.y) continue;

            Point target(i, j, in.getPixel(i, j));
            std::vector<Point> linePoints = performDDA(center, target);

            bool isVisible = true;
            double centerToTargetAngle = calculateAngle(center, target);

            for (const Point& p : linePoints) {
                if (p.x == center.x && p.y == center.y) continue;

                Point current(p.x, p.y, in.getPixel(p.x, p.y));
                double centerToCurrentAngle = calculateAngle(center, current);

                if (centerToCurrentAngle >= centerToTargetAngle) {
                    isVisible = false;
                    break;
                }
            }

            visibility[j][i] = isVisible;
            out.setPixel(i, j, visibility[j][i] ? 255 : 0);
        }
    }

    chr.stop();

    return chr.elapsedTime();
}
