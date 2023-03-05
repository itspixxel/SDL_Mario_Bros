#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>

bool GameScreenLevel1::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Assets/Mario.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
}

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	m_renderer = nullptr;
	delete m_background_texture;
	m_background_texture = nullptr;
}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
}
