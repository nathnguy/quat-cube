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
    SDL_Window* window = SDL_CreateWindow("Quat Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == nullptr) { return 1; }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    
    Cube cube(200, 0, 0, 0);
    Vector3D yAxis(0, 1, 0);
    Vector3D xAxis(1, 0, 0);
    Vector3D zAxis(0, 0, 1);

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
                    cube.rotate(yAxis, 0.03f);
                    break;
                    
            }
        }
        
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

