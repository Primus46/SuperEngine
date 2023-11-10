#include "CoreMinimal.h"
#include "GameObjects/Characters/SECharacter.h"

#include "GameObjects/Components/SESpriteComponent.h"
#include "GameObjects/Components/SEMovementComponent.h"

SECharacter::SECharacter(SEString DefaultName, Window* AssignedWindow) 
	: SEGameObject(DefaultName, AssignedWindow)
{
	m_SpriteComponent = AddComponent<SESpriteComponent>();
	m_MovementComponent = AddComponent<SEMovementComponent>();
	
	SEAnimParams AnimParams;
	AnimParams.FrameCount = 10;
	AnimParams.EndFrame = 9;
	AnimParams.FrameRate = 12.0f;

	GetSpriteComponent()->AddAnimation(
		"EngineContent/Images/SpriteSheets/MainShip/Projectile-Green-10f.png",
		AnimParams);

	AnimParams.FrameCount = 4;
	AnimParams.EndFrame = 3;

	GetSpriteComponent()->AddAnimation(
		"EngineContent/Images/SpriteSheets/MainShip/Projectile-cannon-4f.png",
		AnimParams);
}

void SECharacter::BeginPlay()
{
	SEGameObject::BeginPlay();

	SetPosition(SEVector2(150.0f, 100.0f));
	SetScale(SEVector2(5.0f));

	m_SpriteComponent->SetSpriteIndex(0);

	GetMovementComponent()->AddForce(SEVector2(1.0f, 0.0f), 25.0f);
}

void SECharacter::Update(float DeltaTime)
{
	SEGameObject::Update(DeltaTime);
}
