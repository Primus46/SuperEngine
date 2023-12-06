#include "CoreMinimal.h"
#include "GameObjects/Characters/SECharacter.h"

#include "GameObjects/Components/SESpriteComponent.h"
#include "GameObjects/Components/SEMovementComponent.h"

SECharacter::SECharacter(SEString DefaultName, Window* AssignedWindow) 
	: SEGameObject(DefaultName, AssignedWindow)
{
	m_SpriteComponent = AddComponent<SESpriteComponent>();
	m_MovementComponent = AddComponent<SEMovementComponent>();
}

