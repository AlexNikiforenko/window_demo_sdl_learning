#include "ImageLoader.h"

int main(int argc, char* argv[]) {
    ImageLoader imgLoader;
    imgLoader.init();
    imgLoader.loadTexturesFromDir();
    imgLoader.handleInput();
    imgLoader.close();
}