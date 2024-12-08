#ifndef RENDER_STATE_H
#define RENDER_STATE_H

#include <SDL2/SDL.h>

struct RenderState {
    Uint8 r = 255;
    Uint8 g = 255;
    Uint8 b = 255;
    Uint8 a = 255;
    bool color_switch_flag = false;
    SDL_RendererFlip flipType = SDL_FLIP_NONE;
    double degrees = 0;
};

#endif