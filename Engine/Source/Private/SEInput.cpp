#include "CoreMinimal.h"
#include "SEInput.h"
#include "Game.h"

SEInput::SEInput()
{
	m_KeyboardState = nullptr;
}

SEInput::~SEInput()
{
	m_KeyboardState = nullptr;

}

void SEInput::ProcessInput()
{
	SDL_Event Event;

	while (SDL_PollEvent(&Event)) {
		switch (Event.type) {
		case SDL_MOUSEBUTTONDOWN:
			OnMouseButtonChanged(Event.button, true);
			break;
		case SDL_MOUSEBUTTONUP:
			OnMouseButtonChanged(Event.button, false);
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			m_KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_QUIT:
			Game::GetGameInstance()->EndGame();
			break;
		}
	}
}

bool SEInput::IsKeyDown(SDL_Scancode Key)
{
	if (m_KeyboardState == nullptr) {
		return false;
	}

	return m_KeyboardState[Key];
}

bool SEInput::IsMouseButtonDown(EMouseButtons Button)
{
	return m_MouseStates[Button];
}

void SEInput::OnMouseButtonChanged(SDL_MouseButtonEvent Event, bool IsPressed)
{
	switch (Event.button) {
	case SDL_BUTTON_LEFT:
		m_MouseStates[MB_LEFT] = IsPressed;
		break;
	case SDL_BUTTON_RIGHT:
		m_MouseStates[MB_RIGHT] = IsPressed;
		break;
	case SDL_BUTTON_MIDDLE:
		m_MouseStates[MB_MIDDLE] = IsPressed;
		break;
	}

}
