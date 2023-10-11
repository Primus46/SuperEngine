#pragma once

class SETexture;

class Window {
public:
	Window();
	~Window();

	// Creates Window
	bool CreateWindow(SEString Title, int Width, int Height, SDL_Color Colour = { 30, 30, 30, 255 });

	void Render();

	void Destroy();

	TSharedPtr<SETexture> CreateTexture(SEString PathToFile);

protected:
	virtual void RenderCustomerGraphics();

private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	int m_Width, m_Height;
	SEString m_Title;
	SDL_Color m_BGColour;

	TSharedArray<SETexture> m_TextureStack;
};
