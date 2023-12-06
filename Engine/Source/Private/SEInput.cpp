#include "CoreMinimal.h"
#include "SEInput.h"

#include "Game.h"
#include "Window/Window.h"
#include "Window/SEWindowMenu.h"
#include "SDL2/SDL_syswm.h"
#include "../../resource.h"

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
	// store the inputs pressed in this frame
	SDL_Event Event;

	// find the inputs pressed in the frame and update the Event variable
	// think of this as a event listener
	while (SDL_PollEvent(&Event)) {
		// listen out for different event types
		switch (Event.type) {
		case SDL_MOUSEBUTTONDOWN: // detect if a mouse button is pressed
			OnMouseButtonChanged(Event.button, true);
			break;
		case SDL_MOUSEBUTTONUP: // detect if a mouse button is released
			OnMouseButtonChanged(Event.button, false);
			break;
		case SDL_KEYDOWN: // detect if a key is pressed down or released
		case SDL_KEYUP:
			m_KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_QUIT: // when the cross button is clicked
			Game::GetGameInstance()->EndGame();
			break;
		case SDL_SYSWMEVENT:
			HandleWMEvents(Event);
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

void SEInput::HandleWMEvents(SDL_Event Event)
{
	SEString Title;
	SEString Message;

	switch (Event.syswm.msg->msg.win.wParam)
	{
	case ID_FILE_RESTARTGAME:
		Game::GetGameInstance()->GetWindow()->GetWindowsMenu()->RestartGame();
		break;
	case ID_FILE_EXITAPPLICATION:
		Game::GetGameInstance()->GetWindow()->GetWindowsMenu()->ExitApp();
		break;
	case ID_GAMECONTROLS:
		Title = SEString("Game Controls");
		Message = SEString("A: Move Left\nD: Move Right\nW: Move Forward\nS: Move Backward\n\nMore Controls Coming Soon.");
		Game::GetGameInstance()->GetWindow()->GetWindowsMenu()->ActivatePopup(Title, Message);
		break;
	case ID_HELP_ABOUTSUPERENGINE:
		Title = SEString("About Super Engine");
		Message = SEString("Super Engine is an SDL2-based C++ 2D game engine created by Connor Downey in 2023");
		Game::GetGameInstance()->GetWindow()->GetWindowsMenu()->ActivatePopup(Title, Message);
		break;
	default:
		break;
	}
}
