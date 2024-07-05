#include <shape.h>

using namespace std;

vec2D vec2DNew(float x, float y) {
    vec2D result = {x,y};
    return result;
}

vec2D vec2DAdd(vec2D v1, vec2D v2) {
    vec2D result = {v1.x + v2.x, v1.y + v2.y};
    return result;
}

vec2D vec2DSub(vec2D v1, vec2D v2) {
    vec2D result = {v1.x - v2.x, v1.y - v2.y};
    return result;
}

float vec2DLength(vec2D v) {
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

float vec2DCross(vec2D v1, vec2D v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

Triangle::Triangle(vec2D v0, vec2D v1, vec2D v2) {
    p0 = v0;
    p1 = v1;
    p2 = v2;
    x_min = fmin(fmin(v0.x, v1.x), v2.x);
    y_min = fmin(fmin(v0.y, v1.y), v2.y);
    x_max = fmax(fmax(v0.x, v1.x), v2.x);
    y_max = fmax(fmax(v0.y, v1.y), v2.y);
    e0 = vec2DSub(v1, v0);
    e1 = vec2DSub(v2, v1);
    e2 = vec2DSub(v0, v2);
}

bool Triangle::isPointInTriangle(vec2D p) {
    vec2D v0 = vec2DSub(p, p0);
    vec2D v1 = vec2DSub(p, p1);
    vec2D v2 = vec2DSub(p, p2);
    if (vec2DCross(e0, v0) < 0) {
        return false;
    }
    if (vec2DCross(e1, v1) < 0) {
        return false;
    }
    if (vec2DCross(e2, v2) < 0) {
        return false;
    }
    return true;
}

Circle::Circle(vec2D center, int radius) {
    c = center;
    r = radius;
    x_min = c.x - r;
    y_min = c.y - r;
    x_max = c.x + r;
    y_max = c.y + r;
}

bool Circle::isPointInCircle(vec2D p) {
    if (vec2DLength(vec2DSub(p, c)) > r) {
        return false;
    }
    return true;
}
