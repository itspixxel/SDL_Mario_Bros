#pragma once
#include "Character.h"

class Coin : public Character
{
    public:
        Coin(SDL_Renderer* renderer, Vector2D start_position, Vector2D start_force, LevelMap* map);
        ~Coin();

        void Update(float deltaTime, SDL_Event e) override;
        void Render() override;

        float GetLifetime() const;

    private:
        float m_lifetime;
};
