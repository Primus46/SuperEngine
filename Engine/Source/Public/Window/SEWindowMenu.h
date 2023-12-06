#pragma once

struct SDL_SysWMinfo;

class SEWindowMenu
{
public:
	SEWindowMenu(SDL_Window* Window);
	~SEWindowMenu();

	// Create add the Win32 menu to the SDL window
	void InitialiseMenu();

	// Restart the game
	void RestartGame();

	// Exit the whole app
	void ExitApp();

	// show a simple dialog box with a title and message
	void ActivatePopup(SEString Title, SEString Message);

private:
	// store the owner window that this is attached to
	SDL_Window* m_Window;

	// store the info for a windows menu to convert to SDL
	SDL_SysWMinfo* m_WindowInfo;
};

