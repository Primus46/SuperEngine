#include "CoreMinimal.h"
#include "Graphics/SEText.h"
#include "SDL2/SDL_image.h"

SEText::SEText()
{
	m_Renderer = nullptr;
	m_Text = "Text Block";
	m_FontSize = 36;
	m_Colour = { 255, 255, 255, 255 };
	m_Font = nullptr;
}

SEText::~SEText()
{
	DestroyFont();

}

bool SEText::InportTexture(SDL_Renderer* Renderer, SEString PathToFile)
{
	DestroyFont();

	SELog("Attempting to leod font from path: " + PathToFile);

	m_Font = TTF_OpenFont(PathToFile.c_str(), m_FontSize);

	if (m_Font == nullptr) {
		SELog("Faild to load font - TTF Error " + SEString(TTF_GetError()));
		return false;
	}

	m_Renderer = Renderer;
	m_Path = PathToFile;

	return CreateTextFromFont();
}

void SEText::SetText(SEString Text)
{
	m_Text = Text;

	CreateTextFromFont();
}

void SEText::SetFontSize(int Size)
{
	m_FontSize = Size;

	DestroyFont();

	m_Font = TTF_OpenFont(m_Path.c_str(), m_FontSize);

	if (m_Font == nullptr) {
		SELog("Faild to load font - TTF Error " + SEString(TTF_GetError()));
		return;
	}

	CreateTextFromFont();
}

bool SEText::CreateTextFromFont()
{
	// clear the texture if there already is one
	ClearTexture();

	// import the texture - SDL_Surface - string of pixels
	SDL_Surface* ImageSurface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), m_Colour);

	if (ImageSurface == nullptr) {
		SELog("Font Failed to import: " + m_Path + " - " + TTF_GetError());
		return false;
	}

	// turn the surface into a texture to render to the screen
	m_Texture = SDL_CreateTextureFromSurface(m_Renderer, ImageSurface);

	// set the width and height of the image
	m_ScreenRect.w = m_Width = ImageSurface->w;
	m_ScreenRect.h = m_Height = ImageSurface->h;

	// remove the surface from memory
	SDL_FreeSurface(ImageSurface);

	if (m_Texture == nullptr) {
		SELog("Font Failed to convert to texture: " + m_Path + " - " + SDL_GetError());
		return false;
	}

	// log success
	SELog("Texture loaded successfully: " + m_Path);


	return true;
}

void SEText::DestroyFont()
{
	// destroy curret font if one exists
	if (m_Font != nullptr) {
		TTF_CloseFont(m_Font);
	}
}
