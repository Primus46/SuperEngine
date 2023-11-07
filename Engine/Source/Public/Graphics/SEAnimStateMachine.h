#pragma once

class SEAnimation;
class Window;

class SEAnimStateMachine {
public:
	SEAnimStateMachine();
	~SEAnimStateMachine();

	bool AddAnimation(Window* AssignedWindow, SEString PathToFile, SEAnimParams AnimParams);

	void Start(SEUint StartingIndex = 0);

	void Update(float deltaTime);

	void SetPosition(float X, float Y);

	void SetScale(float W, float H);

	// Change animation to another one
	void SetIndex(SEUint Index);

private:
	TSharedArray<SEAnimation> m_Animations;

	SEUint m_AnimIndex;

	// screen position of the state machine
	float m_PosX, m_PosY;

	// scalar value W & H of the state machine
	float m_ScaleW, m_ScaleH;
};