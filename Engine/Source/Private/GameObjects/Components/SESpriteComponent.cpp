#include "CoreMinimal.h"
#include "GameObjects/Components/SESpriteComponent.h"

#include "Graphics/SEAnimStateMachine.h"
#include "GameObjects/SEGameObject.h"

SESpriteComponent::SESpriteComponent(SEGameObject* Owner)
	: SEComponent(Owner)
{
	m_ASH = new SEAnimStateMachine();
}

bool SESpriteComponent::AddAnimation(SEString PathToFile, SEAnimParams AnimParams)
{
	return m_ASH->AddAnimation(GetOwner()->GetWindow(), PathToFile, AnimParams);
}

bool SESpriteComponent::AddSingleSprite(SEString PathToFile, SESpriteParams SpriteParams)
{
	SEAnimParams AnimParams;
	AnimParams.StartFrame = SpriteParams.Frame;
	AnimParams.EndFrame = SpriteParams.Frame;
	AnimParams.FrameCount = SpriteParams.FrameCount;
	AnimParams.FrameWidth = SpriteParams.FrameWidth;
	AnimParams.FrameHeight = SpriteParams.FrameHeight;
	AnimParams.Row = SpriteParams.Row;
	AnimParams.RowCount = SpriteParams.RowCount;
	AnimParams.FrameRate = 0.0f;
	
	return m_ASH->AddAnimation(GetOwner()->GetWindow(), PathToFile, AnimParams);
 }

void SESpriteComponent::SetSpriteIndex(SEUint Index)
{
	m_ASH->SetIndex(Index);
}

void SESpriteComponent::BeginPlay()
{
	FollowGameObject();

	m_ASH->Start();
}

void SESpriteComponent::Update(float DeltaTime)
{
	FollowGameObject();

	m_ASH->Update(DeltaTime);
}

void SESpriteComponent::OnDestroy()
{
	if (m_ASH != nullptr) {
		delete m_ASH;
	}
}

void SESpriteComponent::FollowGameObject()
{
	m_ASH->SetPosition(
		GetOwner()->GetTransform()->Position.x,
		GetOwner()->GetTransform()->Position.y
	);
	m_ASH->SetScale(
		GetOwner()->GetTransform()->Scale.x,
		GetOwner()->GetTransform()->Scale.y
	);
}
