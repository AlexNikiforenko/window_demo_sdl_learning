#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class ImageLoader {
public:
    bool init();
    void loadTexturesFromDir();
    SDL_Texture* loadTexture(std::string path);

    void renderImage();
    void handleInput();
    void close();
private:
    const int SCREEN_WIDTH = 600;
    const int SCREEN_HEIGHT = 400;

    SDL_Window* window = nullptr;
    SDL_Surface* screen_surface = nullptr;
    SDL_Renderer* renderer = nullptr;

    std::vector<SDL_Texture*> textures;
    int img_idx = 0;
};

#endif