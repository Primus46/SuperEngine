#pragma once

class SEAnimation;
class Window;

class AnimStateMachine {
public:
	AnimStateMachine();
	~AnimStateMachine();

	bool AddAnimation(Window* Assigned, SEString PathToFile, SEAnimParams AnimParams);

	void Update(float deltaTime);

private:
	TSharedArray<SEAnimation> m_Animations;

	SEUint m_AnimIndex;
};