#include "CoreMinimal.h"
#include "Window/Window.h"
#include "Graphics/SETexture.h"

Window::Window()
{
	m_Window = nullptr;
	m_Renderer = nullptr;
	m_Width = m_Height = 0;
	m_Title = "";
	m_BGColour = {};

}

Window::~Window()
{
	m_Window = nullptr;
	m_Renderer = nullptr;

}

bool Window::CreateWindow(SEString Title, int Width, int Height, SDL_Color Colour)
{
	m_Window = SDL_CreateWindow(
		Title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		Width, Height,
		SDL_WINDOW_SHOWN
	);

	if (m_Window == nullptr) {
		std::cout << "SDL window creation failed: " << SDL_GetError() << std::endl;
		return false;
	}
	m_Title = Title;
	m_Width = Width;
	m_Height = Height;
	m_BGColour = Colour;

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (m_Renderer == nullptr) {
		std::cout << "SDL renderer creation failed: " << SDL_GetError() << std::endl;
		Destroy();
		return false;
	}

	return true;
}

void Window::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, m_BGColour.r, m_BGColour.g, m_BGColour.b, m_BGColour.a);

	SDL_RenderClear(m_Renderer);

	RenderCustomerGraphics();

	SDL_RenderPresent(m_Renderer);

}

void Window::Destroy()
{
	if (m_Renderer != nullptr) {
		SDL_DestroyRenderer(m_Renderer);
	}

	if (m_Window != nullptr) {
		SDL_DestroyWindow(m_Window);
	}
}

TSharedPtr<SETexture> Window::CreateTexture(SEString PathToFile)
{
	TSharedPtr<SETexture> NewTexture = TMakeShared<SETexture>();

	if (!NewTexture->InportTexture(m_Renderer, PathToFile)) {
		return nullptr;
	}

	m_TextureStack.push_back(NewTexture);

	return NewTexture;
}

void Window::RenderCustomerGraphics()
{
	for (auto iTexture : m_TextureStack) {
		iTexture->Render(m_Renderer);
	}
}