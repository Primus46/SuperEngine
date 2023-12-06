#include "CoreMinimal.h"
#include "Window/SEWindowMenu.h"

#include "SDL2/SDL_syswm.h"
#include <Windows.h>
#include "../../resource.h"
#include "Game.h"

SEWindowMenu::SEWindowMenu(SDL_Window* Window)
{
	m_Window = Window;
	m_WindowInfo = new SDL_SysWMinfo();

	// Updates the window info with the current SDL version
	SDL_VERSION(&m_WindowInfo->version);

	// after we have the SDl version SDL will allow us to fill in the rest of the window info
	SDL_GetWindowWMInfo(m_Window, m_WindowInfo);
}

SEWindowMenu::~SEWindowMenu()
{
	m_Window = nullptr;

	delete m_WindowInfo;
	m_WindowInfo = nullptr;
}

void SEWindowMenu::InitialiseMenu()
{
	// gets/converts the SDL window info into the system window
	HWND SysWindow = m_WindowInfo->info.win.window;

	// we need to get the resource menu that we created in visual studio
	// GEtModuleHandle(0) get the current instance of the window that we're actively in
	HINSTANCE WindowInstance = GetModuleHandle(0);

	//MAKEINTRESOURCE will convert the menu into a LPCWSTR which is the indes for the menu
	LPCWSTR MenuIndex = MAKEINTRESOURCE(IDR_MENU1);

	// load the menu and save it to a variable
	HMENU SysMenu = LoadMenu(WindowInstance, MenuIndex);

	// add the menu to the window
	if (!SetMenu(SysWindow, SysMenu)) {
		SELog("Menu couldn't be addd to window.");
		return;
	}

	// add an event listener to SDL listen out for Win32 menu buttons
	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
}

void SEWindowMenu::RestartGame()
{
	Game::GetGameInstance()->RestartGame();
}

void SEWindowMenu::ExitApp()
{
	Game::GetGameInstance()->EndGame();
}

void SEWindowMenu::ActivatePopup(SEString Title, SEString Message)
{
	// create a simple message box using SDL
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, Title.c_str(), Message.c_str(), m_Window);
}
