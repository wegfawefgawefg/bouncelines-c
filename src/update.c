/*
    use sdl and cglm (c version of glm) to draw some lines that move around
*/

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <cglm/cglm.h>

#include "update.h"

const float rand_range(float min, float max) {
    return min + (max - min) * (rand() % RAND_MAX / (float)RAND_MAX);
}

float angle = 0.0f;
float angle2 = 0.0f;
float time = 0.0f;

void draw_hand(vec2 start, vec2 end, int depth, int max_depth, SDL_Renderer *renderer) {
    if (depth == max_depth) {
        return;
    }
    //  colors based on depth
    int r = 255 - depth * 10 + time * 150;
    int g = 255 - depth * 9 + rand() % 100;
    int b = 255 - depth * 8;
    SDL_SetRenderDrawColor(renderer, r, g, b, 50);
    SDL_RenderDrawLine(renderer, start[0], start[1], end[0], end[1]);

    vec2 line;
    glm_vec2_sub(end, start, line);
    float scale = glm_vec2_norm(line) * 0.8f;
    glm_vec2_normalize(line);
    glm_vec2_scale(line, scale, line);

    vec2 right_line;
    // float right_angle = angle + (float)depth * time * 1.0;
    glm_vec2_rotate(line, angle2, right_line);
    glm_vec2_add(end, right_line, right_line);
    draw_hand(end, right_line, depth + 1, max_depth, renderer);

    vec2 left_line;
    glm_vec2_rotate(line, -angle, left_line);
    glm_vec2_add(end, left_line, left_line);
    draw_hand(end, left_line, depth + 1, max_depth, renderer);
}

int update_scene(SDL_Renderer *renderer, SDL_Window *window, const Uint8 *keys, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const double dt){
    if (keys[SDL_SCANCODE_Q]) {
        return -1;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    vec2 center = {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f};
    vec2 bottom = {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT};
    vec2 center_to_bottom;
    glm_vec2_sub(bottom, center, center_to_bottom);
    float length = glm_vec2_norm(center_to_bottom) * 0.4f;
    vec2 hand = {0.0f, -length};

    time = SDL_GetTicks() / 1000.0f;
    // glm_vec2_rotate(hand, time, hand);

    vec2 hand_end;
    glm_vec2_add(bottom, hand, hand_end);
    draw_hand(bottom, hand_end, 1, 18, renderer);

    ivec2 mouse;    
    SDL_GetMouseState(&mouse[0], &mouse[1]);

    angle = mouse[0] / (float)WINDOW_WIDTH * 2.0f * M_PI + M_PI;
    angle2 = mouse[1] / (float)WINDOW_HEIGHT * 2.0f * M_PI + M_PI;

    const SDL_Color color = {255, 255, 255, 255};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer, mouse[0], mouse[1]);
    SDL_RenderPresent(renderer);
    return 0;
}