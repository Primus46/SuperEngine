#pragma once

class SETexture;

class SEWindowMenu;

class Window {
public:
	Window();
	~Window();

	// Creates Window
	bool CreateWindow(SEString Title, int Width, int Height, SDL_Color Colour = { 30, 30, 30, 255 });

	void Render();

	void Destroy();

	TSharedPtr<SETexture> CreateTexture(SEString PathToFile);


	// get the win32 menu attached to this window
	SEWindowMenu* GetWindowsMenu() const { return m_WindowMenu; }

protected:
	virtual void RenderCustomerGraphics();

private:
	// store the SDL window
	SDL_Window* m_Window;
	// store the SDL Render
	SDL_Renderer* m_Renderer;
	// store the width and height
	int m_Width, m_Height;
	// store the title  of the window
	SEString m_Title;
	// background colour for the window
	SDL_Color m_BGColour;
	// window texture stack
	TSharedArray<SETexture> m_TextureStack;


	// window menu for the window
	SEWindowMenu* m_WindowMenu;
};
