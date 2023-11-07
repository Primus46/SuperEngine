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

	// process the input each frame
	void ProcessInput();

	// detect when a key is pressed down
	// for release just detect if this is false
	bool IsKeyDown(SDL_Scancode Key);

	// detect when a mouse button is down
	// for release just detect if this is false
	bool IsMouseButtonDown(EMouseButtons Button);

private:
	// listen for mouse button changing
	void OnMouseButtonChanged(SDL_MouseButtonEvent Event, bool IsPressed);

private:
	// store the state of each button on the keeyboard
	const SEUint8* m_KeyboardState;

	// store the state of the 3 main mouse buttons
	bool m_MouseStates[3] = { false };
};
