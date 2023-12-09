#include "CoreMinimal.h"
#include "GameObjects/Characters/SECharacter.h"

#include "GameObjects/Components/SESpriteComponent.h"
#include "GameObjects/Components/SEMovementComponent.h"
#include "GameObjects/Components/SECollisionComponent.h"

SECharacter::SECharacter(SEString DefaultName, Window* AssignedWindow) 
	: SEGameObject(DefaultName, AssignedWindow)
{
	m_CharacterSize = SEVector2(1.0f);
	m_SpriteComponent = AddComponent<SESpriteComponent>();
	m_MovementComponent = AddComponent<SEMovementComponent>();
	m_CollisionComponent = AddComponent<SECollisionComponent>();
	
	// Uncomment below line to view collision Boxes
	// m_CollisionComponent->GetCollision()->Debug = true;
	
}
void SECharacter::BeginPlay()
{
	SEGameObject::BeginPlay();

	m_CollisionComponent->GetCollision()->Bounds.w = GetScaledCharacterSize().x;
	m_CollisionComponent->GetCollision()->Bounds.h = GetScaledCharacterSize().y;
}
SEVector2 SECharacter::GetScaledCharacterSize() const
{
	return GetTransform()->Scale * m_CharacterSize;
}

