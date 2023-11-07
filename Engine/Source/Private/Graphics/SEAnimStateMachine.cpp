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
	m_Animations[m_AnimIndex]->SetPosition(m_PosX, m_PosY);
	m_Animations[m_AnimIndex]->SetPosition(m_ScaleW, m_ScaleH);

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

void SEAnimStateMachine::SetIndex(SEUint Index)
{
	m_Animations[m_AnimIndex]->SetVisibility(false);
	m_AnimIndex = Index;
	m_Animations[m_AnimIndex]->SetVisibility(true);

}
