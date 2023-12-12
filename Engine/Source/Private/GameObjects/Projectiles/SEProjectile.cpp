#include "CoreMinimal.h"
#include "GameObjects/Projectiles/SEProjectile.h"

#include "GameObjects/Components/SECollisionComponent.h"
#include "GameObjects/Components/SEMovementComponent.h"
#include "GameObjects/Components/SESpriteComponent.h"

SEProjectile::SEProjectile(SEString DefaultName, Window* AssignedWindow)
	:SEGameObject(DefaultName, AssignedWindow)
{
	m_Collision = AddComponent<SECollisionComponent>();
	m_Movement = AddComponent<SEMovementComponent>();
	m_Sprite = AddComponent<SESpriteComponent>();

	m_Collision->GetCollision()->Bounds.w = 25.0f;
	m_Collision->GetCollision()->Bounds.h = 25.0f;
	m_Collision->GetCollision()->Debug = true;
}
