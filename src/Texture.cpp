#include "Texture.h"

Texture::Texture() : texture(nullptr), width(0), height(0) {}

Texture::~Texture() {
    std::cout << "DESTRUCTOR\n";
    free();
}

bool Texture::loadFromFile(std::string path, SDL_Renderer* renderer) {
    free(); // Clear previous texture

    SDL_Surface* loaded_surface = IMG_Load(path.c_str());
    if (!loaded_surface) {
        std::cout << "Unable to load image from " <<  path << "! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_Texture* new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);

    if (!new_texture) {
        std::cout << "Unable to create texture from " <<  path << "! SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(loaded_surface);
        return false;
    }

    width = loaded_surface->w;
    height = loaded_surface->h;
    texture = new_texture;

    SDL_FreeSurface(loaded_surface);

    return true;
}

bool Texture::isLoaded() {
    return texture != nullptr;
}

void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip) {
    SDL_Rect renderQuad = {x, y, width, height};

    if (clip) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    if (SDL_RenderCopy(renderer, texture, clip, &renderQuad) < 0) {
        std::cout << "Unable to render copy! SDL Error: " << SDL_GetError() << std::endl;
    }
}

void Texture::free() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        width = 0;
        height = 0;
    }
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}
