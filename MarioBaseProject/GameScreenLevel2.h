#pragma once
#include "GameScreenLevelBase.h"

class GameScreenLevel2 : public GameScreenLevelBase
{
    public:
        GameScreenLevel2(SDL_Renderer* renderer, AudioManager* audio_manager, GameScreenManager* screen_manager, GameSession* session);

        void Update(float deltaTime, SDL_Event e) override;

    private:
        int m_enemy_spawn_side;
        float m_enemy_spawn_timer;

        bool SetUpLevel() override;
        void SetUpEntities() override;

        void UpdateSpawners(float deltaTime);
};
