#include "CoreMinimal.h"
#include "GameObjects/Projectiles/SEPlayerProjectile.h"

#include "GameObjects/Components/SESpriteComponent.h"
#include "GameObjects/Components/SECollisionComponent.h"
#include "GameObjects/Characters/SEEnemy.h"

SEPlayerProjectile::SEPlayerProjectile(SEString DefaultName, Window* AssignedWindow)
	: SEProjectile(DefaultName, AssignedWindow)
{
	GetMainSprite()->AddSingleSprite("EngineContent/Images/SpriteSheets/Projectiles/Projectile_Bolt_1f.png");

	m_CollisionType = SEObjectTypes::OT_ENEMY;

	GetMainCollision()->GetCollision()->Bounds.w = 9.0f;
	GetMainCollision()->GetCollision()->Bounds.h = 34.0f;
}

