#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <fstream>

class ImageLoader {
public:
    bool init();
    void loadImagesFromDir();
    SDL_Surface* loadSurface(std::string path);
    void blitImage();
    void handleInput();
    void clear();
private:
    SDL_Window* window = nullptr;
    SDL_Surface* screen_surface = nullptr;
    SDL_Surface* img = nullptr;

    std::vector<SDL_Surface*> imgs;
    int img_idx = 0;
};

#endif