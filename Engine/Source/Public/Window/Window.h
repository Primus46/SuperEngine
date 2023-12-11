#pragma once

class SETexture;

class SEWindowMenu;
class SEText;

class Window {
public:
	Window();
	~Window();

	// Creates Window
	bool CreateWindow(SEString Title, int Width, int Height, SDL_Color Colour = { 30, 30, 30, 255 });
	// render the memory that the window holds
	void Render();
	// deallocate the memory that the window holds
	void Destroy();
	// create a texture and add it to the texture stack for rendering
	TSharedPtr<SETexture> CreateTexture(SEString PathToFile);

	// create a texture and add it to the texture stack for rendering
	TSharedPtr<SEText> CreateText(SEString PathToFile);

	// remove the texture from the texture stack in the window
	// rember that if you are referenceing this anywhere else remove that reference too
	void RemoveTexture(TSharedPtr<SETexture> Texture);

	// get the width of the window
	int GetWidth() const { return m_Width; }
	// get the height of the window
	int GetHeight() const { return m_Height; }

	// get the win32 menu attached to this window
	SEWindowMenu* GetWindowsMenu() const { return m_WindowMenu; }

protected:
	// render custom graphics for the game engine
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
	// window text stack
	TSharedArray<SEText> m_TextStack;


	// window menu for the window
	SEWindowMenu* m_WindowMenu;
};
