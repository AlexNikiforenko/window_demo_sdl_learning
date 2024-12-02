#include "ImageLoader.h"

int main(int argc, char* argv[]) {
    ImageLoader imgLoader;
    imgLoader.init();
    //imgLoader.loadMedia();
    imgLoader.loadImagesFromDir();
    imgLoader.blitImage();
    imgLoader.handleInput();
    imgLoader.clear();
}