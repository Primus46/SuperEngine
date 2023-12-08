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
	SEAnimParams m_AnimParams;

	TSharedPtr<SETexture> m_SpriteSheet;

	float FrameTimer;

	SEUint CurrentFrame;
};