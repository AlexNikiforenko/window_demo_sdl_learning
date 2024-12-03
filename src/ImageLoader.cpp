#include "ImageLoader.h"

bool ImageLoader::init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL couldn't be initialized! SDL error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // Create window
    window = SDL_CreateWindow("Naruto", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Window couldn't be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer couldn't be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Initialize image loading
    int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init(img_flags) & img_flags)) {
        std::cout << "SDL_image couldn't initialize! SDL_image error: " << SDL_GetError() << std::endl;
        return false;
    }

    screen_surface = SDL_GetWindowSurface(window);
    return true;
}

void ImageLoader::loadTexturesFromDir() {
    namespace fs = std::filesystem;
    std::vector<fs::directory_entry> dirents{fs::directory_iterator("../resources/"), fs::directory_iterator{}};

    textures.reserve(dirents.size());

    for (const auto& dir: dirents) {
        SDL_Texture* texture = loadTexture(dir.path().string());
        if (!texture) {
            std::cout << dir.path().string() << " wasn't succesfully load" << std::endl;
            continue;
        }
        textures.push_back(texture);
    }
}

SDL_Texture* ImageLoader::loadTexture(std::string path) {
    SDL_Texture* new_texture = nullptr;

    SDL_Surface* loaded_surface = IMG_Load(path.c_str());
    if (!loaded_surface) {
        std::cout << "Unable to load image from " <<  path << "! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if (!new_texture) {
        std::cout << "Unable to create texture from " <<  path << "! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_FreeSurface(loaded_surface);

    return new_texture;
}

void ImageLoader::renderImage() {
    std::cout << "rendered\n";

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textures[img_idx], nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void ImageLoader::handleInput() {
    SDL_Event e;
    bool quit = false;
    while(!quit){
        while(SDL_PollEvent(&e) )
        {
            if (img_idx < 0) img_idx = textures.size() - 1;
            if (img_idx >= textures.size()) img_idx = 0;
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
            renderImage();
        }
    }
}

void ImageLoader::close() {
    for (auto& texture : textures) {
        if (texture) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
    textures.clear();

    if (screen_surface) {
        SDL_FreeSurface(screen_surface);
        screen_surface = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    IMG_Quit();
    SDL_Quit();
}