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
SDL_Surface* xOut = NULL;

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

    return success;
    }
}

bool loadMedia()
{
    // flag for loading success
    bool success = true;

    // load splash image
    xOut = SDL_LoadBMP("x.bmp");

    // if surface fails to load   
    if(xOut == NULL)
    {
        printf("Unable to load image %s. SDL error: %s\n", "x.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}

void closeWindow()
{
    // deallocate surface
    SDL_FreeSurface( xOut );

    // destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    // quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char** argv)
{
    // start SDL and create window
    bool initSuccess = init();

    if(!initSuccess)
    {
        printf("Failed to initialize.\n" );
    }
    else
    {
        // load media
        bool loadSuccess = loadMedia();
        if(!loadSuccess)
        {
            printf("Failed to load media.\n" );
        }
        else
        {
            // main loop flag
            bool quit = false;

            // event handler
            SDL_Event e;
            
            // while program is running
            while( !quit )
            {
                // handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    // SDL_PollEvent returns 0 if the queue is empty.
                    // Loop body executes if there was something in the queue.

                    // user requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                }

                // apply image
                SDL_BlitSurface( xOut, NULL, gScreenSurface, NULL);

                // update surface
                SDL_UpdateWindowSurface( gWindow );
            }
        }
    }

    // free resources and close SDL
    closeWindow();

    return 0;
}
