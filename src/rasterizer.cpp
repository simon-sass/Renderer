#include <rasterizer.h>
#include <iostream>

Rasterizer::Rasterizer() {
    framebuffer = nullptr;
}

Rasterizer::Rasterizer(uint32_t* frame) {
    framebuffer = frame;
}

void Rasterizer::drawPixel(uint16_t x, uint16_t y, uint32_t color) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return;
    }
    framebuffer[(SCREEN_WIDTH * y) + x] = color;
}

void Rasterizer::clearFramebuffer(uint32_t color) {
    for (size_t i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        framebuffer[i] = color;
    }
}

void Rasterizer::drawLine(vec2D v1, vec2D v2) {

}

void Rasterizer::drawTriangle(Triangle triangle) {
    int x_min = triangle.x_min*(triangle.x_min>0);
    int y_min = triangle.y_min*(triangle.y_min>0);
    for (size_t y = y_min; y <= triangle.y_max; y++) {
        for (size_t x = x_min; x <= triangle.x_max; x++) {
            vec2D p = {x,y};
            if (triangle.isPointInTriangle(p)) {
                drawPixel(x, y, white);
            }
        }
    }
}

void Rasterizer::drawCircle(Circle circle) {
    int x_min = circle.x_min*(circle.x_min>0);
    int y_min = circle.y_min*(circle.y_min>0);
    for (size_t y = y_min; y <= circle.y_max; y++) {
        for (size_t x = x_min; x <= circle.x_max; x++) {
            vec2D p = {x,y};
            if (circle.isPointInCircle(p)) {
                drawPixel(x, y, white);
            }
        }
    }
}