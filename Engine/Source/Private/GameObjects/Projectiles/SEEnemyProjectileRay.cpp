#include "CoreMinimal.h"
#include "GameObjects/Projectiles/SEEnemyProjectileRay.h"

#include "GameObjects/Components/SESpriteComponent.h"
#include "GameObjects/Components/SECollisionComponent.h"
#include "GameObjects/Components/SEMovementComponent.h"

SEEnemyProjectileRay::SEEnemyProjectileRay(SEString DefaultName, Window* AssignedWindow)
	:SEProjectile(DefaultName, AssignedWindow)
{
	SEAnimParams AnimParams;
	AnimParams.EndFrame = 3;
	AnimParams.FrameCount = 4;
	AnimParams.FrameRate = 24;

	GetMainSprite()->AddAnimation(
		"EngineContent/Images/SpriteSheets/Enemies/Weapons/Projectiles/Kla'ed - Ray - 4f.png",
		AnimParams
	);

	m_Damage = 5;

	SetRotation(180.0f);

	m_CollisionType = SEObjectTypes::OT_PLAYER;

	GetMainCollision()->GetCollision()->Bounds.w = 16.0f;
	GetMainCollision()->GetCollision()->Bounds.h = 16.0f;

	m_MoveDirection = SEVector2(0.0f, 1.0f);

	// GetMainCollision()->GetCollision()->Debug = true;

	GetTransform()->Scale *= 2.0f;

	GetMainCollision()->GetCollision()->Bounds.w = 18.0f * GetTransform()->Scale.x;
	GetMainCollision()->GetCollision()->Bounds.h = 38.0f * GetTransform()->Scale.y;

	GetMovementComponent()->m_MaxVelocity = 200;
}
