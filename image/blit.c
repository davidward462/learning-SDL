#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// ----- Global variables -----

// the window we are rendering to
SDL_Window *gWindow = NULL;

// the surface contained by the window
SDL_Surface* gScreenSurface = NULL;

// the image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

// --------------------------------

// startup SDL and create window
bool init();

// load Media
bool loadMedia();

// Frees media and shuts down SDL
void closeWindow();


bool init()
{
    bool success = true;

    // initialize
    // Getting -1 would indicate an error.
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf("SDL could not be initialized. SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow( "SDL tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        
        // if there is an erorr when creating the window
        if(gWindow == NULL)
        {
            printf("Window could not be created. SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            // get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow);
        }
    }

    return success;
}

bool loadMedia()
{
    // flag for loading success
    bool success = true;

    // load splash image
    gHelloWorld = SDL_LoadBMP("hello_world.bmp");

    // if surface fails to load   
    if(gHelloWorld == NULL)
    {
        printf("Unable to load image %s. SDL error: %s\n", "hello_world.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}

void closeWindow()
{
    // deallocate surface
    SDL_FreeSurface( gHelloWorld );

    // destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    // quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char** argv)
{



    return 0;
}
