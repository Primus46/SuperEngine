#include "CoreMinimal.h"
#include "GameObjects/Projectiles/SEEnemyProjectileSmall.h"

#include "GameObjects/Components/SESpriteComponent.h"
#include "GameObjects/Components/SECollisionComponent.h"
#include "GameObjects/Components/SEMovementComponent.h"

SEEnemyProjectileSmall::SEEnemyProjectileSmall(SEString DefaultName, Window* AssignedWindow)
	:SEProjectile(DefaultName, AssignedWindow)
{
	SEAnimParams AnimParams;
	AnimParams.EndFrame = 3;
	AnimParams.FrameCount = 4;
	AnimParams.FrameRate = 24;

	GetMainSprite()->AddAnimation(
		"EngineContent/Images/SpriteSheets/Enemies/Weapons/Projectiles/Kla'ed - Bullet - 4f.png",
		AnimParams
	);

	SetRotation(180.0f);

	m_CollisionType = SEObjectTypes::OT_PLAYER;

	GetMainCollision()->GetCollision()->Bounds.w = 16.0f;
	GetMainCollision()->GetCollision()->Bounds.h = 16.0f;

	m_MoveDirection = SEVector2(0.0f, 1.0f);

	// GetMainCollision()->GetCollision()->Debug = true;

	GetTransform()->Scale *= 2.0f;

	GetMainCollision()->GetCollision()->Bounds.w = 4.0f * GetTransform()->Scale.x;
	GetMainCollision()->GetCollision()->Bounds.h = 14.0f * GetTransform()->Scale.y;

	GetMovementComponent()->m_MaxVelocity = 200;
}
