#include <iostream>
#include <shape.h>
#include <rasterizer.h>

int main() {
    uint32_t* framebuffer = (uint32_t*)malloc(sizeof(uint32_t) * SCREEN_WIDTH * SCREEN_HEIGHT);
    Rasterizer rasterizer = Rasterizer(framebuffer);
    Triangle triangle = Triangle({12, 3}, {20, 20}, {5, 17});
    rasterizer.clearFramebuffer(black);
    rasterizer.drawTriangle(triangle);
    rasterizer.drawPixel(12, 13, white);
    std::cout << rasterizer.framebuffer[13*SCREEN_WIDTH+12] << std::endl;
}