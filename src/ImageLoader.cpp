#include "ImageLoader.h"

bool ImageLoader::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL INIT ERROR: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    window = SDL_CreateWindow("Naruto", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "SDL WINDOW INIT ERROR: " << SDL_GetError() << std::endl;
        return false;
    }
    screen_surface = SDL_GetWindowSurface(window);
    return true;
}

void ImageLoader::loadImagesFromDir() {
    namespace fs = std::filesystem;
    std::vector<fs::directory_entry> dirents{fs::directory_iterator("../resources/"), fs::directory_iterator{}};

    imgs.reserve(dirents.size());

    for (const auto& dir: dirents) {
        SDL_Surface* img = loadSurface(dir.path().string());
        if (!img) {
            std::cout << dir.path().string() << " wasn't succesfully load" << std::endl;
            continue;
        }
        imgs.push_back(img);
    }
}

SDL_Surface* ImageLoader::loadSurface(std::string path) {
    img = SDL_LoadBMP(path.c_str());
    if (!img) {
        std::cout << "Unable to load image: " <<  path << " " << SDL_GetError() << std::endl;
        return nullptr;
    }
    std::cout << path << " was succesfully loaded" << std::endl;
    return img;
}

void ImageLoader::blitImage() {
    std::cout << "blit\n";
    SDL_BlitSurface(imgs[img_idx], nullptr, screen_surface, nullptr);
    SDL_UpdateWindowSurface(window);
}

void ImageLoader::handleInput() {
    SDL_Event e;
    bool quit = false;
    while(!quit){
        while(SDL_PollEvent(&e) )
        {
            if (img_idx < 0) img_idx = imgs.size() - 1;
            if (img_idx >= imgs.size()) img_idx = 0;
            //if (img_idx < 0) img_idx = imgs.size() - 1;
            if(e.type == SDL_QUIT)
                quit = true;
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                img_idx++;
            }
            else if(e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_RIGHT:
                        img_idx++;
                        break;
                    case SDLK_LEFT:
                        img_idx--;
                        break;
                }
            }
            std::cout << img_idx << std::endl;
            blitImage();
        }
    }
}

void ImageLoader::clear() {
    for (auto& img : imgs) {
        if (img) {
            SDL_FreeSurface(img);
            img = nullptr;
        }
    }
    imgs.clear();

    if (screen_surface) {
        SDL_FreeSurface(screen_surface);
        screen_surface = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}