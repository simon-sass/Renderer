#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <cstdint>
#include <shape.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define white 0xFFFFFFFF
#define black 0x000000FF

class Rasterizer {
    public:
    uint32_t* framebuffer;
    Rasterizer();
    Rasterizer(uint32_t* framebuffer);
    void drawPixel(uint16_t x, uint16_t y, uint32_t color);
    void clearFramebuffer(uint32_t color);
    void drawLine(vec2D v1, vec2D v2);
    void drawTriangle(Triangle triangle);
    void drawCircle(Circle circle);
};

#endif