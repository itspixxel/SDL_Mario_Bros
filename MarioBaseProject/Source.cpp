//Be grateful for humble beginnings, because the next level will always require so much more of you
// That's deep^^

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"

using namespace std;

// Function prototypes
void CLoseSDL();
void Render();
void FreeTexture();
bool InitSDL();
bool Update();
SDL_Texture* LoadTextureFromFile(string path);

// Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_texture = nullptr;

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
		cout << "SDL did not initialise. Error: " << SDL_GetError();
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
			cout << "Window was not created. Error: " << SDL_GetError();
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
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}

			//Load the background texture
			g_texture = LoadTextureFromFile("Assets/Mario.bmp");
			if (g_texture == nullptr)
			{
				return false;
			}

		}
		else
		{
			// Renderer failed
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
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

	// Clear the texture
	FreeTexture();

	// Release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

}

void Render()
{
	// Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 24, 24, 24, 255);
	SDL_RenderClear(g_renderer);

	// Set where to render the texture
	SDL_Rect renderLocation = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

	//Render to screen
	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);

	// Update the screen
	SDL_RenderPresent(g_renderer);
}

void FreeTexture()
{

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

SDL_Texture* LoadTextureFromFile(string path)
{
	// Remove the memory used for a previous texture
	FreeTexture();

	SDL_Texture* p_texture = nullptr;

	//Load the image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		//create the texture from the pixels on the surface
		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
		if (p_texture == nullptr)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}
		//remove the loaded surface now that we have a texture
		SDL_FreeSurface(p_surface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError();
	}

	return p_texture;
}
