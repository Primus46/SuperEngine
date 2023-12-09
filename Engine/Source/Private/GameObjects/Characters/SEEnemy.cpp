#include "CoreMinimal.h"
#include "GameObjects/Characters/SEEnemy.h"
#include "GameObjects/Components/SESpriteComponent.h"
#include "GameObjects/Components/SEMovementComponent.h"
#include "GameObjects/Components/SECollisionComponent.h"
#include "Window/Window.h"

SEEnemy::SEEnemy(SEString DefaultName, Window* AssignedWindow) 
	: SECharacter(DefaultName, AssignedWindow)
{
	m_CharacterSize = SEVector2(64.0f);
	m_EngineEffects = AddComponent<SESpriteComponent>();

	// add ship sprite to the main sprite component
	GetSpriteComponent()->AddSingleSprite("EngineContent/Images/SpriteSheets/Enemies/Base/Kla'ed - Fighter - Base.png");

	SEAnimParams AnimParams;
	AnimParams.EndFrame = 9;
	AnimParams.FrameCount = 10;
	
	m_EngineEffects->AddAnimation(
		"EngineContent/Images/SpriteSheets/Enemies/EngineEffects/Kla'ed - Fighter - Engine-10f.png",
		AnimParams);

	// moves down the screen from the get go
	m_MovementDir = SEVector2(0.0f, 1.0f);

	m_EnemyAcceleration = 100.0f;
	GetMovementComponent()->m_MaxVelocity = 100.0f;
	GetMovementComponent()->m_Drag = -5.0f;

	SetRotation(180.0f);
	SetScale(2.0f);

}

void SEEnemy::Update(float DeltaTime)
{
	SECharacter::Update(DeltaTime);
	
	GetMovementComponent()->AddForce(m_MovementDir, m_EnemyAcceleration);
	
	if (GetTransform()->Position.y > GetWindow()->GetHeight()) {
		SetPosition({ GetTransform()->Position.x, -GetScaledCharacterSize().y});
	}

}

void SEEnemy::BeginPlay()
{
	SECharacter::BeginPlay();

	GetCollisionComponent()->GetCollision()->Bounds.w = GetScaledCharacterSize().x * 0.5;
	GetCollisionComponent()->GetCollision()->Bounds.h = GetScaledCharacterSize().y * 0.5;
	GetCollisionComponent()->BoundsOffset.x = 32.0f;
	GetCollisionComponent()->BoundsOffset.y = 22.0f;
}
