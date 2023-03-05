#pragma once

#ifndef _GAMESCREENLVL1_H
#define _GAMESCREENLVL1_H

#include <SDL.h>
#include <string>
#include "GameScreen.h"
#include "commons.h"
class Texture2D;

class GameScreenLevel1 : GameScreen
{
	private:
		Texture2D* m_background_texture;
		bool SetUpLevel();

	public:
		GameScreenLevel1(SDL_Renderer* renderer);
		~GameScreenLevel1();

		void Render() override;
		void Update(float deltaTime, SDL_Event e) override;


};

#endif _GAMESCREENLVL1_H