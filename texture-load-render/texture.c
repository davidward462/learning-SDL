// Standard header files
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// SDL header files
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Set up SDL
bool Init();

bool LoadMedia();

// Free surfaces and shutdown SDL
bool CloseWindow();

// load image as texture
SDL_Texture* loadTexture(char* path);

int main(int argc, char **argv)
{
    return 0;
}
