#include <rasterizer.h>
#include <iostream>

color rgb[3] = {
    {0xFF, 0x00, 0x00},
    {0x00, 0xFF, 0x00},
    {0x00, 0x00, 0xFF}
};

color colors[3] = {
    {0xFD, 0x78, 0x8B},
    {0xFE, 0xDC, 0xDB},
    {0xFE, 0x66, 0x94}
};

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
                float w0 = vec2DCross(triangle.e1, vec2DSub(p,triangle.p1)) / triangle.area;
                float w1 = vec2DCross(triangle.e2, vec2DSub(p,triangle.p2)) / triangle.area;
                float w2 = vec2DCross(triangle.e0, vec2DSub(p,triangle.p0)) / triangle.area;

                int r = w0*rgb[0].r + w1*rgb[1].r + w2*rgb[2].r;
                int g = w0*rgb[0].g + w1*rgb[1].g + w2*rgb[2].g;
                int b = w0*rgb[0].b + w1*rgb[1].b + w2*rgb[2].b;
                int a = 0xFF;

                uint32_t interp = 0x00000000;
                interp = (interp | a) << 8;
                interp = (interp | r) << 8;
                interp = (interp | g) << 8;
                interp = (interp | b) << 8;

                drawPixel(x, y, interp);
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