#include "CoreMinimal.h"
#include "Graphics/SETexture.h"
#include "SDL2/SDL_image.h"

SETexture::SETexture()
{
	m_ScreenRect = { 0, 0, 0, 0 };
	m_ClipRect = nullptr;
	m_Texture = nullptr;
	m_Width = m_Height = 0;
	m_ScalarW = m_ScalarH = 1.0f;
	m_Visibility = true;
	m_Rotation = 0.0;
}

SETexture::~SETexture()
{
	ClearTexture();
}

bool SETexture::InportTexture(SDL_Renderer* Renderer, SEString PathToFile)
{
	if (m_Texture != nullptr) {
		ClearTexture();
	}

	SDL_Surface* ImageSurface = IMG_Load(PathToFile.c_str());

	if (ImageSurface == nullptr) {
		SELog("Image Failed to import: " + PathToFile + " - " + SDL_GetError());
		return false;
	}

	m_Texture = SDL_CreateTextureFromSurface(Renderer, ImageSurface);

	m_ScreenRect.w = m_Width = ImageSurface->w;
	m_ScreenRect.h = m_Height = ImageSurface->h;


	m_Path = PathToFile;

	SDL_FreeSurface(ImageSurface);

	if (m_Texture == nullptr) {
		SELog("Image Failed to convert to texture: " + PathToFile + " - " + SDL_GetError());
		return false;
	}

	SELog("Texture loaded successfully: " + m_Path);

	return true;
}

void SETexture::Render(SDL_Renderer* Renderer)
{
	if (!m_Visibility) {
		return;
	}

	SDL_FRect ScaledScreenRect = m_ScreenRect;
	ScaledScreenRect.w *= m_ScalarW;
	ScaledScreenRect.h *= m_ScalarH;

	SDL_RenderCopyExF(
		Renderer,
		m_Texture,
		m_ClipRect,
		&ScaledScreenRect,
		m_Rotation,
		nullptr,
		SDL_FLIP_NONE
		);
}

void SETexture::ClearTexture()
{
	if (m_ClipRect != nullptr) {
		SDL_DestroyTexture(m_Texture);
	}
	
	if (m_ClipRect != nullptr) {
		delete m_ClipRect;
	}
}

void SETexture::SetPosition(float X, float Y)
{
	m_ScreenRect.x = X;
	m_ScreenRect.y = Y;
}

void SETexture::SetDimensions(float W, float H)
{
	m_ScreenRect.w = W;
	m_ScreenRect.h = H;
}

void SETexture::SetScale(float W, float H)
{
	m_ScalarW = W;
	m_ScalarH = H;
}

void SETexture::SetClip(int X, int Y, int W, int H)
{
	if (m_ClipRect == nullptr) {
		m_ClipRect = new SDL_Rect();
	}

	m_ClipRect->x = X;
	m_ClipRect->y = Y;
	m_ClipRect->w = W;
	m_ClipRect->h = H;
}
