#include <iostream>
#include <shape.h>

int main() {
    Triangle triangle = Triangle({1, 2}, {3, 4}, {5, 10});
    std::cout << triangle.e2.x << triangle.e2.y << std::endl;
}