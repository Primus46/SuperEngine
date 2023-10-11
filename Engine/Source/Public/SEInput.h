#pragma once

enum EMouseButtons : SEUint8 {
	MB_LEFT = 0,
	MB_RIGHT = 1,
	MB_MIDDLE = 2
};

class SEInput {
public:
	SEInput();
	~SEInput();

	void ProcessInput();

	bool IsKeyDown(SDL_Scancode Key);

	bool IsMouseButtonDown(EMouseButtons Button);

private:
	void OnMouseButtonChanged(SDL_MouseButtonEvent Event, bool IsPressed);

private:
	const SEUint8* m_KeyboardState;

	bool m_MouseStates[3] = { false };
};
