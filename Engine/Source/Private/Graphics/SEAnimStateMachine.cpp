#include "CoreMinimal.h"
#include "Graphics/SEAnimStateMachine.h"
#include "Graphics/SEAnimation.h"

SEAnimStateMachine::SEAnimStateMachine()
{
	m_AnimIndex = 0;
	m_PosX = m_PosY = 0.0f;
	m_ScaleW = m_ScaleH = 1.0f;
}

SEAnimStateMachine::~SEAnimStateMachine()
{
	m_Animations.clear();
}

bool SEAnimStateMachine::AddAnimation(Window* AssignedWindow, SEString PathToFile, SEAnimParams AnimParams)
{
	TSharedPtr<SEAnimation> NewAnim = TMakeShared<SEAnimation>();

	// validates if the new animation was successfully created
	if (!NewAnim->InportAnimation(AssignedWindow, PathToFile, AnimParams)) {
		SELog("Animation Failed to import into anim state machine.");
		return false;
	}

	// hide animation by default
	NewAnim->SetVisibility(false);

	// added new animation to the animation stack
	m_Animations.push_back(NewAnim);

	return true;
}

void SEAnimStateMachine::Start(SEUint StartingIndex)
{
	SetIndex(StartingIndex);
}

void SEAnimStateMachine::Update(float deltaTime)
{
	if (m_Animations.size() <= m_AnimIndex) {
		return;
	}
	
	UpdateAnimTransforms();

	m_Animations[m_AnimIndex]->Update(deltaTime);
}

void SEAnimStateMachine::SetPosition(float X, float Y)
{
	m_PosX = X;
	m_PosY = Y;
}

void SEAnimStateMachine::SetScale(float W, float H)
{
	m_ScaleW = W;
	m_ScaleH = H;
}

void SEAnimStateMachine::SetRotation(float NewRot)
{
	m_Rotation = NewRot;
}

void SEAnimStateMachine::SetIndex(SEUint Index)
{
	if (m_Animations.size() <= Index) {
		SELog("no animation/sprite exists at that index.");
		return;
	}
	// hide current animation
	m_Animations[m_AnimIndex]->SetVisibility(false);
	// change the anim index to play a diffferent animation
	m_AnimIndex = Index;
	// update the transform of that animation to make sure it's in the correct position
	UpdateAnimTransforms();
	// show the animation on the screen
	m_Animations[m_AnimIndex]->SetVisibility(true);

}

void SEAnimStateMachine::UpdateAnimTransforms()
{
	m_Animations[m_AnimIndex]->SetPosition(m_PosX, m_PosY);
	m_Animations[m_AnimIndex]->SetScale(m_ScaleW, m_ScaleH);
	m_Animations[m_AnimIndex]->SetRotation(m_Rotation);
}
