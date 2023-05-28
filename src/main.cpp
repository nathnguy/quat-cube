//
//  main.cpp
//  quat-cube
//
//  Created by Nathan on 5/23/23.
//

#include <SDL.h>
#include <SDL_image.h>
#include "Cube.hpp"

void render(SDL_Renderer*, const Cube&);
void handleKeyPress(SDL_KeyboardEvent* key, bool rotatingAxes[]);
void handleKeyRelease(SDL_KeyboardEvent* key, bool rotatingAxes[]);
void keyRotate(Cube& cube, Vector3D axes[], bool rotatingAxes[]);

int main(int argc, const char * argv[]) {
    
    const int WINDOW_WIDTH = 500;
    const int WINDOW_HEIGHT = 500;
    
    const int FPS = 60;
    const int FRAME_DELAY = 1000 / FPS;
    
    Uint32 frameStart;
    int frameTime;
    
    // Init video subsystem. Return 1 on error.
    if (SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) { return 1; }

    // Create window
    SDL_Window* window = SDL_CreateWindow("quat-cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == nullptr) { return 1; }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    
    Cube cube(200, 0, 0, 0);
    cube.rotate(Vector3D(0, 1, 0), 0.785398f);
    cube.rotate(Vector3D(1, 0, 0), 0.6245f);
//    cube.rotate(Vector3D(0, 0, 1), 0.785398f);
    
    Vector3D axes[] = {
        Vector3D(-1, 0, 0), // w
        Vector3D(0, 1, 0), // a
        Vector3D(1, 0, 0), // s
        Vector3D(0, -1, 0)  // d
    };
    
    bool rotatingAxes[] = {false, false, false, false};

    // Loop forever to stop window from closing right away.
    bool running = true;
    while (running) {
        frameStart = SDL_GetTicks();
        
        // We'll poll for events here. Catch the quit event.
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    handleKeyPress(&event.key, rotatingAxes);
                    break;
                case SDL_KEYUP:
                    handleKeyRelease(&event.key, rotatingAxes);
                    break;
                default:
                    break;
                    
            }
        }
        
        keyRotate(cube, axes, rotatingAxes);
        
        render(renderer, cube);
        
        frameTime = SDL_GetTicks() - frameStart;
        
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    // Cleanup
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    // Done!
    return 0;
}

void render(SDL_Renderer* renderer, const Cube& cube) {
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 100, 189, 124, 255);
    
    cube.draw(renderer);
    
    // set background color
    SDL_SetRenderDrawColor(renderer, 135, 135, 135, 255);
    
    SDL_RenderPresent(renderer);
}

void handleKeyPress(SDL_KeyboardEvent* key, bool rotatingAxes[]) {
    switch(key->keysym.sym) {
        case SDLK_w:
            rotatingAxes[0] = true;
            break;
        case SDLK_a:
            rotatingAxes[1] = true;
            break;
        case SDLK_s:
            rotatingAxes[2] = true;
            break;
        case SDLK_d:
            rotatingAxes[3] = true;
            break;
        default:
            break;
    }
}

void handleKeyRelease(SDL_KeyboardEvent* key, bool rotatingAxes[]) {
    switch(key->keysym.sym) {
        case SDLK_w:
            rotatingAxes[0] = false;
            break;
        case SDLK_a:
            rotatingAxes[1] = false;
            break;
        case SDLK_s:
            rotatingAxes[2] = false;
            break;
        case SDLK_d:
            rotatingAxes[3] = false;
            break;
        default:
            break;
    }
}

void keyRotate(Cube& cube, Vector3D axes[], bool rotatingAxes[]) {
    for (int i = 0; i < 4; ++i) {
        if (rotatingAxes[i]) {
            cube.rotate(axes[i], 0.03f);
        }
    }
}
