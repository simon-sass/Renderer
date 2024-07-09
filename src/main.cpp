#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <shape.h>
#include <rasterizer.h>

#undef main

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

SDL_Texture* framebufferTexture;
uint32_t* framebuffer;

SDL_Event windowEvent;

Rasterizer rasterizer;

bool isRunning = false;

Triangle triangle = Triangle({50., 200.}, {500., 200.}, {50., 450.});
Circle circle = Circle({800., 600.}, 100);

Triangle triangles[3] = {
    Triangle({10, 10}, {20, 10}, {10, 20}),
    Triangle({20, 10}, {20, 20}, {10, 20}),
    Triangle({30, 30}, {40, 55}, {20, 50})
};

void renderFramebuffer() {
    SDL_UpdateTexture(
        framebufferTexture,
        NULL,
        framebuffer,
        (int)(SCREEN_WIDTH * sizeof(uint32_t))
    );
    SDL_RenderCopy(renderer, framebufferTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void loop() {
    while (isRunning) {
        if (SDL_PollEvent(&windowEvent)) {
            if (SDL_QUIT == windowEvent.type) {
                break;
            }
        }
        rasterizer.clearFramebuffer(black);
        triangles[0].rotate(0.005, {15, 15});
        triangles[1].rotate(0.005, {15, 15});
        triangles[2].rotate(0.005, {40, 30});
        rasterizer.drawTriangle(triangles[0]);
        rasterizer.drawTriangle(triangles[1]);
        rasterizer.drawTriangle(triangles[2]);
        renderFramebuffer();
    }
}

bool createWindow() {
    SDL_Init(SDL_INIT_EVERYTHING); 

    window = SDL_CreateWindow("Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (!window) {
        cout << "Error creating SDL window" << endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cout << "Error creating SDL renderer" << endl;
        return false;
    }

    framebuffer = (uint32_t*)malloc(sizeof(uint32_t) * SCREEN_WIDTH * SCREEN_HEIGHT);
    if (!framebuffer) {
        cout << "Error allocating memory for framebuffer" << endl;
        return false;
    }

    framebufferTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ABGR32,
        SDL_TEXTUREACCESS_STREAMING,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );

    rasterizer = Rasterizer(framebuffer);

    return true;
}

void killWindow() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    isRunning = createWindow();

    loop();

    killWindow();

    return EXIT_SUCCESS;
}
