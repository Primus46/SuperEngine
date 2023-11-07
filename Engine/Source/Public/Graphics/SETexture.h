#pragma once

class SETexture {
public:
	SETexture();
	~SETexture();

	bool InportTexture(SDL_Renderer* Renderer, SEString PathToFile);

	void Render(SDL_Renderer* Renderer);

	void ClearTexture();

	inline SEUint GetWidth() const { return m_Width; }

	inline SEUint GetHeight() const { return m_Height; }

	void SetPosition(float X, float Y);

	void SetDimensions(float W, float H);

	void SetScale(float W, float H);

	void SetClip(int X, int Y, int W, int H);

	inline void SetVisibility(bool IsVisibile) { m_Visibility = IsVisibile; }
	
	inline bool GetVisibility() const { return m_Visibility; }

private:
	SDL_FRect m_ScreenRect;

	SDL_Rect* m_ClipRect;

	SDL_Texture* m_Texture;

	SEString m_Path;

	SEUint m_Width, m_Height;

	float m_ScalarW, m_ScalarH;

	bool m_Visibility;
};