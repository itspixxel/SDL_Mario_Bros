#include "GameScreen1.h"
#include <iostream>
#include "Texture2D.h"


GameScreen1::GameScreen1(SDL_Renderer* renderer): GameScreen(renderer)
{
	SetUpLevel();
	m_level_map = nullptr; 
}

GameScreen1::~GameScreen1()
{
	delete m_background_texture;
	m_background_texture = nullptr; 
	delete mario;
	mario = nullptr;
	delete luigi; 
	luigi = nullptr;
	delete m_pow_block;
	m_pow_block = nullptr;
}

void GameScreen1::Render()
{
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	mario->Render();
	luigi->Render();
	m_pow_block->Render();
}

void GameScreen1::Update(float deltaTime, SDL_Event e)
{
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}

	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);
	UpdatePowBlock();

	if (Collisions::Instance()->Circle(mario, luigi))
	{
		std::cout << "Circle hit!" << std::endl;
	}
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	{
		std::cout << "Box hit!" << std::endl;
	}
	

}

void GameScreen1::UpdatePowBlock()
{
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), m_pow_block->GetCollisionsBox()) && m_pow_block->IsAvailable())
	{
		//collided while jumping
		if (mario->IsJumping())
		{
			DoScreenShake();
			m_pow_block->TakeHit();
			mario->CancelJump();
		}

	}
}

bool GameScreen1::SetUpLevel()
{
	
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Assets/Background.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	mario = new CharacterMario(m_renderer, "Assets/Mario.png", Vector2D(64, 330), m_level_map);
	luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330), m_level_map);

	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false; 
	m_background_yPos = 0.0f; 
	return false;
}

void GameScreen1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
					  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);

}

void GameScreen1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

}
