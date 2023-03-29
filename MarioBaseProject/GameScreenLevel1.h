#pragma once

#include <SDL.h>
#include <string>
#include "GameScreen.h"
#include "commons.h"
class Texture2D;
class Character;

class GameScreenLevel1 : GameScreen
{
	private:
		Texture2D* m_background_texture;
		Character* my_character;
		bool SetUpLevel();

	public:
		GameScreenLevel1(SDL_Renderer* renderer);
		~GameScreenLevel1();

		void Render() override;
		void Update(float deltaTime, SDL_Event e) override;
};