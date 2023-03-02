//Be grateful for humble beginnings, because the next level will always require so much more of you
// That's deep^^

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "commons.h"
#include "Texture2D.h"

using namespace std;

// Function prototypes
void CLoseSDL();
void Render();
bool InitSDL();
bool Update();

// Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
Texture2D* g_texture = nullptr;

int main(int argc, char* args[])
{
	// Check if sdl was setup correctly
	if (InitSDL())
	{
		// Flag to check if we wish to quit
		bool quit = false;

		// Game loop
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}

	CLoseSDL();

	return 0;
}

bool InitSDL()
{
	// Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// SDL failed
		cout << "ERROR: SDL did not initialise." << endl << SDL_GetError() << endl;
		return false;
	}
	else
	{
		// Setup passed so create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		// Did the window get created?
		if (g_window == nullptr)
		{
			// Window failed
			cout << "ERROR: Window was not created." << endl << SDL_GetError() << endl;
			return false;
		}

		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		// Did the renderer get created?
		if (g_renderer != nullptr)
		{
			// Init PNG loading
			int imageFlags = IMG_INIT_PNG;
			// Check if image initialized
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				// Image failed
				cout << "ERROR: SDL_Image could not initialise." << endl << IMG_GetError() << endl;
				return false;
			}

			//Load the background texture
			g_texture = new Texture2D(g_renderer);

			if (!g_texture->LoadFromFile("Assets/Mario.png"))
			{
				return false;
			}


		}
		else
		{
			// Renderer failed
			cout << "ERROR: Renderer could not initialise." << endl << SDL_GetError() << endl;
			return false;
		}
	}

}

void CLoseSDL()
{
	// Release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	//release the texture
	delete g_texture;
	g_texture = nullptr;

	// Release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

}

void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	g_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//update the screen
	SDL_RenderPresent(g_renderer);

}

bool Update()
{
	// Event Handler
	SDL_Event e;

	// Get Events
	SDL_PollEvent(&e);

	// Handle the events
	switch (e.type)
	{
		// Click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;
	}
	return false;
}
