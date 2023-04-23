#pragma once
#include "GameScreen.h"
#include "TextBox.h"

class GameScreenError : public GameScreen
{
    public:
        GameScreenError(SDL_Renderer* renderer, AudioManager* audio_manager, GameSession* session);
        ~GameScreenError();

        bool Setup() override;
        void Render() override;

    private:
        Font* m_font;
        TextBox* m_line_1;
        TextBox* m_line_2;
        SDL_Cursor* m_system_err_cursor;
};