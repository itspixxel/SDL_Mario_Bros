#include "GameScreenIntro.h"

#include <iostream>
#include <sstream>

#include "TextBox.h"

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer, AudioManager* audio_manager, GameScreenManager* screen_manager, GameSession* session) :
    GameScreen(renderer, audio_manager, session),
    m_screen_manager(screen_manager),
    m_background_texture(nullptr),
    m_hud_font(nullptr),
    m_text_2p(nullptr),
    m_text_high_scores(nullptr),
    m_text_mouse_pos(nullptr),
    m_mouse_x(0),
    m_mouse_y(0)
{

}

GameScreenIntro::~GameScreenIntro()
{
    delete m_background_texture;
    delete m_hud_font;
}

bool GameScreenIntro::Setup()
{
    m_background_texture = new Texture2D(m_renderer);
    if (!m_background_texture->LoadFromFile("Assets/Title_BG.png"))
    {
        std::cout << "Failed to load background texture!" << std::endl;
        return false;
    }

    if (!SetBackgroundMusic("Audio/Music/MarioUnderworld.mp3"))
    {
        return false;
    }

    m_hud_font = new Font(m_renderer, "Fonts/Super-Mario-World.ttf", 16);
    if (!m_hud_font->IsLoaded())
    {
        return false;
    }

    m_text_2p = new TextBox(m_hud_font, "..... START  (2p) .....", { 256, 270 + 15 }, TextColor::BLACK, TextColor::WHITE, false, TextAlignHorizontal::CENTER);
    //m_text_high_scores = new TextBox(m_hud_font, ".... HIGH SCORES ....", { 256, 300 }, TextColor::WHITE, TextColor::BLACK, false, TextAlignHorizontal::CENTER);
    
    return true;
}

void GameScreenIntro::Render()
{
    m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

    m_text_2p->Draw();
    //m_text_high_scores->Draw();
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
    switch (e.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            switch (e.button.button)
            {
                case SDL_BUTTON_LEFT:
                    if (CheckTextBoxHover(m_text_2p))
                    {
                        m_session->players = 2;
                        m_screen_manager->QueueScreen(Screen::LEVEL_1);
                    }
                    /*else if (CheckTextBoxHover(m_text_high_scores))
                    {
                        m_screen_manager->QueueScreen(Screen::HIGH_SCORES);
                    }*/
                    break;
        }
    }

    SDL_GetMouseState(&m_mouse_x, &m_mouse_y);

    m_text_2p->SetDrawBg(CheckTextBoxHover(m_text_2p));
    //m_text_high_scores->SetDrawBg(CheckTextBoxHover(m_text_high_scores));
}


bool GameScreenIntro::CheckTextBoxHover(TextBox* text_box) const
{
    SDL_Rect bounds = text_box->GetBoundingBox();

    return bounds.x < m_mouse_x && bounds.x + bounds.w > m_mouse_x
        && bounds.y < m_mouse_y && bounds.y + bounds.h > m_mouse_y;
}
