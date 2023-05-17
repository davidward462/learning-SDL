#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char** argv)
{
    // window to which we are rendering
    SDL_Window* window = NULL;

    // surface contained by the window
    SDL_Surface* screenSurface = NULL;

    // initialize
    // Getting -1 would indicate an error.
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf("SDL could not be initialized. SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        // Create window
        window = SDL_CreateWindow( "SDL tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        
        // if there is an erorr when creating the window
        if(window == NULL)
        {
            printf("Window could not be created. SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            // get window surface
            screenSurface = SDL_GetWindowSurface( window);

            // fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF) );

            // update the surface. 
            // Do this, or else the changes will not be shown.
            SDL_UpdateWindowSurface( window );

            // Make the window stay up
            SDL_Event e; bool quit = false; while(quit == false) { while(SDL_PollEvent(&e)){ if(e.type == SDL_QUIT ) quit = true; } }
        }

    }

    // destory the window
    SDL_DestroyWindow( window);

    // quit subsystems
    SDL_Quit();

    return 0;
}
