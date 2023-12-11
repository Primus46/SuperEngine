#pragma once

class Window;
class SETexture;

class SEAnimation {
public:
	SEAnimation();
	~SEAnimation();
	// this will import a sprite sheet use anim params to set up for play
	bool InportAnimation(Window* AssignedWindow, SEString PathToFile, SEAnimParams AnimParams);
	// update the timer logic to switch animation frames
	void Update(float DeltaTime);
	// set the screen position of the animation
	void SetPosition(int X, int Y);
	// set the scale of the animation
	void SetScale(int W, int H);
	// set the rotation of the animation
	void SetRotation(float NewRot);
	// set the animation visibility
	void SetVisibility(bool IsVisible);

private:
	void ClipAnimation();
private:
	// animation paramaters for play rate
	SEAnimParams m_AnimParams;

	// spritsheet texture
	TSharedPtr<SETexture> m_SpriteSheet;

	// time since the last frame
	float FrameTimer;

	// current frame playing in the animation
	SEUint CurrentFrame;

	// store the window this animation is assigned to 
	Window* m_Window;
};