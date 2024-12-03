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
    void loadImagesFromDir();
    SDL_Surface* loadSurface(std::string path);
    void blitImage();
    void handleInput();
    void clear();
private:
    const int SCREEN_WIDTH = 600;
    const int SCREEN_HEIGHT = 400;
    SDL_Window* window = nullptr;
    SDL_Surface* screen_surface = nullptr;
    SDL_Surface* img = nullptr;

    std::vector<SDL_Surface*> imgs;
    int img_idx = 0;
};

#endif