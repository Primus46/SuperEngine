#pragma once

class Window;
class SETexture;

class SEAnimation {
public:
	SEAnimation();
	~SEAnimation();

	bool InportAnimation(Window* AssignedWindow, SEString PathToFile, SEAnimParams AnimParams);

	void Update(float DeltaTime);

	void SetPosition(int X, int Y);

	void SetScale(int W, int H);

private:
	void ClipAnimation();
private:
	SEAnimParams m_AnimParams;

	TSharedPtr<SETexture> m_SpriteSheet;

	float FrameTimer;

	SEUint CurrentFrame;
};