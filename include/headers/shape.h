#include <vector>
#include <cmath>

using namespace std;

#pragma once

typedef struct {
    float x, y;
} vec2D;

vec2D vec2DNew(float x, float y);
vec2D vec2DAdd(vec2D v1, vec2D v2);
vec2D vec2DSub(vec2D v1, vec2D v2);
vec2D vec2DMul(vec2D v, float factor);
float vec2DLength(vec2D v);
float vec2DDot(vec2D v1, vec2D v2);
float vec2DCross(vec2D v1, vec2D v2);

class Triangle {
    public:
    vec2D p0, p1, p2;
    vec2D e0, e1, e2;
    int x_min, y_min, x_max, y_max;
    Triangle(vec2D v0, vec2D v1, vec2D v2);
    bool isPointInTriangle(vec2D p);
};

class Circle {
    public:
    int r, x_min, y_min, x_max, y_max;
    vec2D c;
    Circle(vec2D center, int radius);
    bool isPointInCircle(vec2D p);
};

