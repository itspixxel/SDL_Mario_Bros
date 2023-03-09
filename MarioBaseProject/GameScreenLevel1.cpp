#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Character.h"
#include <iostream>

bool GameScreenLevel1::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Assets/background.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	my_character = new Character(m_renderer, "Assets/Mario.png", Vector2D(64, 330));
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

	delete my_character;
	my_character = nullptr;
}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	my_character->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	my_character->Update(deltaTime, e);
}
