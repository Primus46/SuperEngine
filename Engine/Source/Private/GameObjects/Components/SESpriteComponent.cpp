#include "CoreMinimal.h"
#include "GameObjects/Components/SESpriteComponent.h"

#include "Graphics/SEAnimStateMachine.h"
#include "GameObjects/SEGameObject.h"

SESpriteComponent::SESpriteComponent(SEGameObject* Owner)
	: SEComponent(Owner)
{
	m_ASM = new SEAnimStateMachine();
}

bool SESpriteComponent::AddAnimation(SEString PathToFile, SEAnimParams AnimParams)
{
	return m_ASM->AddAnimation(GetOwner()->GetWindow(), PathToFile, AnimParams);
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
	
	return m_ASM->AddAnimation(GetOwner()->GetWindow(), PathToFile, AnimParams);
 }

void SESpriteComponent::SetSpriteIndex(SEUint Index)
{
	m_ASM->SetIndex(Index);
}

void SESpriteComponent::BeginPlay()
{
	FollowGameObject();

	m_ASM->Start();
}

void SESpriteComponent::Update(float DeltaTime)
{
	FollowGameObject();

	m_ASM->Update(DeltaTime);
}

void SESpriteComponent::ClearSprites()
{
	m_ASM->ClearAllAnimations();
}

void SESpriteComponent::OnDestroy()
{
	if (m_ASM != nullptr) {
		delete m_ASM;
	}
}

void SESpriteComponent::FollowGameObject()
{
	// set the position of the anim state machine to the owner object
	m_ASM->SetPosition(
		GetOwner()->GetTransform()->Position.x,
		GetOwner()->GetTransform()->Position.y
	);

	// set the Scale of the anim state machine to the owner object
	m_ASM->SetScale(
		GetOwner()->GetTransform()->Scale.x,
		GetOwner()->GetTransform()->Scale.y
	);

	// set the Rotation of the anim state machine to the owner object
	m_ASM->SetRotation(GetOwner()->GetTransform()->Rotation);
}
