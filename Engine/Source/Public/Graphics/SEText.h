#pragma once
#include "SETexture.h"
#include "SDL2/SDL_ttf.h"

class SEText :
    public SETexture
{
public:
    SEText();
    ~SEText();

    // import font into a texture
    virtual bool InportTexture(SDL_Renderer* Renderer, SEString PathToFile) override;
    
    // change the text of the text
    void SetText(SEString Text);

    // update the size of the font in px
    void SetFontSize(int Size);

private:
    bool CreateTextFromFont();

    void DestroyFont();

private:
    // store the renderer 
    SDL_Renderer* m_Renderer;

    // the string of letters that make up the text
    SEString m_Text;

    // the size of the font in px
    int m_FontSize;

    // the colour of the font
    SDL_Color m_Colour;

    // the loaded font
    TTF_Font* m_Font;
};

