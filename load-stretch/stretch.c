#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// ----- Function prototypes -----

// startup SDL and create window
bool init();

// load Media
bool loadMedia();

// Frees media and shuts down SDL
void closeWindow();

// Loads individual image
SDL_Surface* loadSurface(const char *file);

// ----- Global variables -----

// Key press surface constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

// the window we are rendering to
SDL_Window *gWindow = NULL;

// the surface contained by the window
SDL_Surface* gScreenSurface = NULL;

// The images that correspond to a key press
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

// Current displayed image
SDL_Surface* gCurrentSurface = NULL;
        
// --------------------------------

bool init()
{
    printf("call success()...\n");
    bool success = true;

    // initialize
    // Getting -1 would indicate an error.
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf("SDL could not be initialized. SDL_Error: %s\n", SDL_GetError() );
        success = false;
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
    printf("call loadMedia()...\n");
    // flag for loading success
    bool success = true;

    //load default surface 
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface( "bmp/press.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        printf("Failed to load default image.\n");
        success = false;
    }

	//Load up surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "bmp/up.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
	{
		printf( "Failed to load up image!\n" );
		success = false;
	}

	//Load down surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "bmp/down.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
	{
		printf( "Failed to load down image!\n" );
		success = false;
	}

	//Load left surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "bmp/left.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
	{
		printf( "Failed to load left image!\n" );
		success = false;
	}

	//Load right surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "bmp/right.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
	{
		printf( "Failed to load right image!\n" );
		success = false;
	}

    return success;
}

void closeWindow()
{
    printf("Call closeWindow()...\n");
    // deallocate surfaces
    for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) // why pre-increment?
    {
		SDL_FreeSurface( gKeyPressSurfaces[ i ] );
		gKeyPressSurfaces[ i ] = NULL;
    }

    // destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    // quit SDL subsystems
    SDL_Quit();
}

SDL_Surface* loadSurface(const char *file)
{
    printf("Call loadedSurface(%s)...\n", file);
    SDL_Surface* loadedSurface = SDL_LoadBMP(file);
    if(loadedSurface == NULL)
    {
        printf("Unable to load image %s. SDL error: %s\n", file, SDL_GetError() );
    }
    
    return loadedSurface;
}

int main(int argc, char** argv)
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set default current surface
			gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

            // while program is running
            while( !quit )
            {
                // handle events on queue
                while( SDL_PollEvent( &e ) != 0)
                {
                    // user requests to quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    else if ( e.type == SDL_KEYDOWN )
                    {
                        //Select surfaces based on key press
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_UP:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                            break;

                            case SDLK_DOWN:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                            break;

                            case SDLK_LEFT:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                            break;

                            case SDLK_RIGHT:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                            break;

                            default:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                            break;
                        }
                    }
                }

                // Apply the current image 
                SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL);

                // Update the surface
                SDL_UpdateWindowSurface( gWindow );

            } // end 'while program is running' loop
        }
    }

    return 0;
}
