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

Triangle triangle = Triangle({535, 35}, {676, 504}, {214, 296});
Circle circle = Circle({400, 300}, 100);

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
        //rasterizer.drawTriangle(triangle);
        rasterizer.drawCircle(circle);
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
