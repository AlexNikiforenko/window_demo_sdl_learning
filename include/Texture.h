#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(std::string path, SDL_Renderer* renderer);
    bool isLoaded();

    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);

    //void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr);
    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,
                SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    void free();

    int getWidth();
    int getHeight();

private:
    SDL_Texture* texture;

    int width;
    int height;
};

#endif