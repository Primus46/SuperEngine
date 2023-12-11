#include "CoreMinimal.h"
#include "Window/Window.h"
#include "Graphics/SETexture.h"
#include "Graphics/SEText.h"
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
	// creaste a shared ptr instead of an object pointer
	TSharedPtr<SETexture> NewTexture = TMakeShared<SETexture>();

	// if the texture fails to import nullptr
	if (!NewTexture->InportTexture(m_Renderer, PathToFile)) {
		return nullptr;
	}

	//if it succeededs add it to the stack
	m_TextureStack.push_back(NewTexture);

	return NewTexture;
}

TSharedPtr<SEText> Window::CreateText(SEString PathToFile)
{
	// creaste a shared ptr instead of an object pointer
	TSharedPtr<SEText> NewTexture = TMakeShared<SEText>();

	// if the texture fails to import nullptr
	if (!NewTexture->InportTexture(m_Renderer, PathToFile)) {
		return nullptr;
	}

	//if it succeededs add it to the stack
	m_TextStack.push_back(NewTexture);

	return NewTexture;
}

void Window::RemoveTexture(TSharedPtr<SETexture> Texture)
{
	if (dynamic_cast<SEText*>(Texture.get())) {
		// find the iterator for the texture in the texture stack
		auto it = std::find(m_TextStack.begin(), m_TextStack.end(), Texture);

		// if we didn't find the texture - do nothing
		if (it == m_TextStack.end()) {
			return;
		}

		// remove the item from the array
		// being a shared pointer as long as nothing else references it, th texture will auto delete
		m_TextStack.erase(it);

		return;
	}

	// find the iterator from the texture in the texture stack
	auto it = std::find(m_TextureStack.begin(), m_TextureStack.end(), Texture);

	// if we didn't find teh texture - do nothing
	if (it == m_TextureStack.end()) {
		return;
	}

	// remove the item from the array
	// being a sharded pointer as long as nothing else refernces it, the texture will auto delete
	m_TextureStack.erase(it);
}

void Window::RenderCustomerGraphics()
{	
	// loop over each element in the array and run the render function
	// iTexture will represent the element of each loop
	for (auto iTexture : m_TextureStack) {
		iTexture->Render(m_Renderer);
	}

	// loop over all of the text objects and render them on top of the images
	for (auto iText : m_TextStack) {
		iText->Render(m_Renderer);
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
