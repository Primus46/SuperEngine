#pragma once

class SEAnimation;
class Window;

class SEAnimStateMachine {
public:
	SEAnimStateMachine();
	~SEAnimStateMachine();

	// create and add an animation to the state machine
	bool AddAnimation(Window* AssignedWindow, SEString PathToFile, SEAnimParams AnimParams);

	void Start(SEUint StartingIndex = 0);

	void Update(float deltaTime);
	// set the screen position for all animations
	void SetPosition(float X, float Y);
	// set the width and height for all animations
	void SetScale(float W, float H);

	// set the rotation of all animations in the state machine
	void SetRotation(float NewRot);
	// Change animation to another one
	void SetIndex(SEUint Index);
	
private:
	// update the transforms of animations to match teh state machine
	void UpdateAnimTransforms();

private:
	// this stores all the animations
	TSharedArray<SEAnimation> m_Animations;
	// this will help us get the animation we want
	SEUint m_AnimIndex;

	// screen position of the state machine
	float m_PosX, m_PosY;

	// scalar value W & H of the state machine
	float m_ScaleW, m_ScaleH;

	// rotation value for the anim state machine
	float m_Rotation;
};