#include "CoreMinimal.h"
#include "Window/Window.h"
#include "Graphics/SETexture.h"
#include "Game.h"
#include "Collisions/SECollisionEngine.h"
#include "Collisions/SECollision.h"

#include "Window/SEWindowMenu.h"


Window::Window()
{
	m_Window = nullptr;
	m_Renderer = nullptr;
	m_Width = m_Height = 0;
	m_Title = "";
	m_BGColour = {};
	m_WindowMenu = nullptr;
}

Window::~Window()
{
	m_Window = nullptr;
	m_Renderer = nullptr;
	delete m_WindowMenu;
	m_WindowMenu = nullptr;
}

bool Window::CreateWindow(SEString Title, int Width, int Height, SDL_Color Colour)
{
	// use SDL to create a window
	m_Window = SDL_CreateWindow(
		Title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		Width, Height,
		SDL_WINDOW_SHOWN
	);

	// id the window failed to create
	if (m_Window == nullptr) {
		std::cout << "SDL window creation failed: " << SDL_GetError() << std::endl;
		return false;
	}

	// if the window was successful store the variables
	m_Title = Title;
	m_Width = Width;
	m_Height = Height;
	m_BGColour = Colour;

	// create a renderer using SDL
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_PRESENTVSYNC);

	// if the render failed to create
	if (m_Renderer == nullptr) {
		std::cout << "SDL renderer creation failed: " << SDL_GetError() << std::endl;
		Destroy();
		return false;
	}

	// create a window menu
	m_WindowMenu = new SEWindowMenu(m_Window);
	m_WindowMenu->InitialiseMenu();

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
	// loop over each element in the array and run the render function
	// iTexture will represent the element of each loop
	for (auto iTexture : m_TextureStack) {
		iTexture->Render(m_Renderer);
	}

	// draw collisions that are set to debug
	for (auto Col : Game::GetGameInstance()->GetCollisions()->GetCollisions()) {
		if (!Col->Debug) {
			continue;
		}

		// set teh draw rect to the same value as out bounds
		SDL_FRect DrawRect;
		DrawRect.x = Col->Bounds.x;
		DrawRect.y = Col->Bounds.y;
		DrawRect.w = Col->Bounds.w;
		DrawRect.h = Col->Bounds.h;

		// this sets the colour of the box
		SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
		SDL_RenderDrawRectF(m_Renderer, &DrawRect);
	}
}
