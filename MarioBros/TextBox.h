#pragma once
#include "Font.h"

class TextBox
{
    public:
        TextBox(Font* font, std::string text = "", Vector2D position = { 0, 0 }, SDL_Color text_color = TextColor::WHITE, SDL_Color bg_color = TextColor::BLACK, bool draw_bg = false, TextAlignHorizontal align_x = TextAlignHorizontal::LEFT, TextAlignVertical align_y = TextAlignVertical::TOP);
        ~TextBox();

        Font* GetFont() const;
        std::string GetText() const;
        Vector2D GetPosition() const;
        SDL_Color GetTextColor() const;
        SDL_Color GetBgColor() const;
        bool GetDrawBg() const;
        TextAlignHorizontal GetAlignX() const;
        TextAlignVertical GetAlignY() const;

        void SetFont(Font* font);
        void SetText(std::string text);
        void SetPosition(Vector2D position);
        void SetTextColor(SDL_Color text_color);
        void SetBgColor(SDL_Color bg_color);
        void SetDrawBg(bool draw_bg);
        void SetAlignX(TextAlignHorizontal align_x);
        void SetAlignY(TextAlignVertical align_y);

        void Draw() const;
        SDL_Rect GetBoundingBox();

    private:
        Font* m_font;
        std::string m_text;
        Vector2D m_position;
        SDL_Color m_text_color;
        SDL_Color m_bg_color;
        bool m_draw_bg;
        TextAlignHorizontal m_align_x;
        TextAlignVertical m_align_y;
};
