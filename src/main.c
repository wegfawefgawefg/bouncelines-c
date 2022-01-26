/*
    use sdl and cglm (c version of glm) to draw some lines that move around
*/

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cglm/cglm.h>

#include "update.h"

// static const int WINDOW_WIDTH = 800;
// static const int WINDOW_HEIGHT = 600;
static const int WINDOW_WIDTH = 1920;
static const int WINDOW_HEIGHT = 1080;

int main(int argc, char *argv[]){
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 16);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    SDL_Renderer *renderer;
    SDL_Window *window;
    window = SDL_CreateWindow("Bounceline", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    Uint64 frame_time_now = SDL_GetPerformanceCounter();
    Uint64 frame_time_last = 0;
    double dt = 0;

    SDL_Event event;
    while (1) {
        frame_time_last = frame_time_now;
        frame_time_now = SDL_GetPerformanceCounter();
        dt = (double)((frame_time_now - frame_time_last)*1000 / (double)SDL_GetPerformanceFrequency() );

        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }
        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        if(update_scene(renderer, window, keys, WINDOW_WIDTH, WINDOW_HEIGHT, dt) != 0 ){
            break;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
