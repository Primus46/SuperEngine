#include "CoreMinimal.h"
#include "GameObjects/Characters/SEEnemyShooter.h"

#include "GameObjects/Components/SESpriteComponent.h"
#include "GameObjects/Components/SECollisionComponent.h"
#include "GameObjects/Projectiles/SEEnemyProjectileSmall.h"
#include "Game.h"
#include "GameObjects/Components/SEMovementComponent.h"

SEEnemyShooter::SEEnemyShooter(SEString DefaultName, Window* AssignedWindow)
	:SEEnemy(DefaultName, AssignedWindow)
{
	m_CharacterSize = SEVector2(88.0f);

	

	GetSpriteComponent()->ClearSprites();

	GetSpriteComponent()->AddSingleSprite("EngineContent/Images/SpriteSheets/Enemies/Base/Kla'ed - Frigate - Base.png");

	SEAnimParams AnimParams;
	AnimParams.EndFrame = 11;
	AnimParams.FrameCount = 12;

	m_EngineEffects->AddAnimation(
		"EngineContent/Images/SpriteSheets/Enemies/EngineEffects/Kla'ed - Frigate - Engine - 12f.png",
		AnimParams);

	m_Value = 20;
	m_Lives = 3;

	m_ShootTimer = 0.0f;
	m_FireRate = 2.0f;

	GetMovementComponent()->m_MaxVelocity = 75.0f;
}

void SEEnemyShooter::BeginPlay()
{
	SECharacter::BeginPlay();
	GetCollisionComponent()->GetCollision()->Bounds.w = GetScaledCharacterSize().x * 0.5;
	GetCollisionComponent()->GetCollision()->Bounds.h = GetScaledCharacterSize().y * 0.5;

	GetCollisionComponent()->BoundsOffset.x = 20.0f;
	GetCollisionComponent()->BoundsOffset.y = 20.0f;
}

void SEEnemyShooter::Update(float DeltaTime)
{
	SEEnemy::Update(DeltaTime);
	TryShoot();


	if (m_ShootTimer < m_FireRate) {
		m_ShootTimer += DeltaTime;
	}
}

void SEEnemyShooter::TryShoot()
{
	if (m_ShootTimer >= m_FireRate) {
		m_ShootTimer = 0.0f;

		SEEnemyProjectileSmall* Proj = Game::GetGameInstance()->AddGameObject<SEEnemyProjectileSmall>();

		SEVector2 SpawnPos = (GetTransform()->Position + (GetScaledCharacterSize() * 0.5f));
		SpawnPos.x -= 27.0f;
		SpawnPos.y += 20.0f;
		Proj->SetPosition(SpawnPos);
	}
}
