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
	// set the scale of the whole image
	void SetScale(float W, float H);
	// set the clip range of the image
	void SetClip(int X, int Y, int W, int H);
	// set the visibilitty of the texture
	void SetVisibility(bool IsVisibile) { m_Visibility = IsVisibile; }
	// get the visibilitty of the texture
	bool GetVisibility() const { return m_Visibility; }
	// rotate the angle of the texture
	void SetRotation(double NewRot) { m_Rotation = NewRot; }

private:
	// hold the screen position and scale of the texture
	SDL_FRect m_ScreenRect;
	// the clip value for the textur
	SDL_Rect* m_ClipRect;
	// hld the SDL version of our texture
	SDL_Texture* m_Texture;
	// store the original file path
	SEString m_Path;
	// original image width and height
	SEUint m_Width, m_Height;
	// scalar values to multiple the size of the image
	float m_ScalarW, m_ScalarH;
	// hide the texture
	bool m_Visibility;
	// angle rotation of the sprite
	double m_Rotation;
};