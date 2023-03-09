#include "Character.h"
#include <string>
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position)
{
	m_renderer = renderer;
	m_texture = new Texture2D(m_renderer);
	m_position = start_position;
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load Character Texture" << std::endl;
	}
}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
}

void Character::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
			case SDLK_d || SDLK_RIGHT:
				m_position.x -= 1;
			break;
		}
		break;

	default:
		break;
	}
}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}
