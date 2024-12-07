#include "ImageLoader.h"

ImageLoader::ImageLoader() : r(0), g(0), b(0), img_idx(0),
                color_switch_flag(false) {
    init();
}

ImageLoader::~ImageLoader() {
    close();
}

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
    // Get images filepaths from directory
    namespace fs = std::filesystem;
    std::vector<fs::directory_entry> dirents{fs::directory_iterator("../resources/"), fs::directory_iterator{}};

    textures.reserve(dirents.size());

    // Load images to textures
    for (const auto& dir: dirents) {
        std::string path = dir.path();

        Texture* texture = new Texture;
        if (!texture->loadFromFile(path, renderer)) {
            std::cout << path << " wasn't succesfully load" << std::endl;
            continue;
        }

        textures.push_back(texture);
        std::cout << path << " was loaded" << std::endl;
    }
}

void ImageLoader::renderTexture(Texture* texture) {
    if (!texture->isLoaded()) {
        std::cout << "Texture is null during rendering!" << std::endl;
        return;
    }
    std::cout << "rendered\n";

    SDL_RenderClear(renderer);
    texture->render(renderer, 0, 0);
    //SDL_RenderPresent(renderer);
}

void ImageLoader::handleInput() {
    SDL_Event e;
    bool quit = false;

    while(!quit){
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                quit = true;

            handleKeyEvent(e);
            handleMouseEvent(e);

            std::cout << img_idx << std::endl;
            img_idx = (img_idx + textures.size()) % textures.size(); // keeps bounds of vector correct
            if (color_switch_flag) {
                textures[img_idx]->setColor(r, g, b);
                std::cout << "r: " << (int)r << " g: " << (int)g << " b: " << (int)b << std::endl;
            }
            else {
                textures[img_idx]->setColor(255, 255, 255);
            }
            renderTexture(textures[img_idx]);
            SDL_RenderPresent(renderer);
        }
    }
}

void ImageLoader::handleKeyEvent(SDL_Event& e) {
    if(e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_RIGHT:
                img_idx++;
                break;
            case SDLK_LEFT:
                img_idx--;
                break;
            case SDLK_q:
                r += 32;
                break;
            case SDLK_w:
                g += 32;
                break;
            case SDLK_e:
                b += 32;
                break;
            case SDLK_a:
                r -= 32;
                break;
            case SDLK_s:
                g -= 32;
                break;
            case SDLK_d:
                b -= 32;
                break;
            case SDLK_c:
                color_switch_flag = !color_switch_flag;
                if (color_switch_flag) {
                    std::cout << "Color mode enabled" << std::endl;
                }
                else {
                    std::cout << "Color mode disabled" << std::endl;
                }
                break;
        }
    }
}

void ImageLoader::handleMouseEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        img_idx++;
    }
}

void ImageLoader::close() {
    // Clear all textures from array
    for (auto& texture : textures) {
        if (texture) {
            delete texture;
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