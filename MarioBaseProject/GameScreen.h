#pragma once

#include <SDL.h>
#include <string>
#include "commons.h"

class GameScreen
{
	protected:
		SDL_Renderer* m_renderer;

	public:
		GameScreen(SDL_Renderer* renderer);
		~GameScreen();

		virtual void Render();
		virtual void Update(float deltaTime, SDL_Event e);

};