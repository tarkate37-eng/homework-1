#pragma once

#include <cmath>

struct Point {
    double x{ 0.0 };
    double y{ 0.0 };

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// Компаратор: сравнивает точки по расстоянию до (0, 0)
// Используем (x^2 + y^2), чтобы не тратить время на вычисление квадратного корня
struct ComparePointByOriginDist {
    bool operator()(const Point& a, const Point& b) const noexcept {
        return (a.x * a.x + a.y * a.y) < (b.x * b.x + b.y * b.y);
    }
};