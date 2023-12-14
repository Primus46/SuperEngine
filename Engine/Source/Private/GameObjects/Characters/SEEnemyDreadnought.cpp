#include "CoreMinimal.h"
#include "GameObjects/Characters/SEEnemyDreadnought.h"

#include "GameObjects/Components/SESpriteComponent.h"
#include "GameObjects/Components/SECollisionComponent.h"
#include "GameObjects/Projectiles/SEEnemyProjectileRay.h"
#include "Game.h"
#include "GameObjects/Components/SEMovementComponent.h"


SEEnemyDreadnought::SEEnemyDreadnought(SEString DefaultName, Window* AssignedWindow)
	:SEEnemy(DefaultName, AssignedWindow)
{
	m_CharacterSize = SEVector2(180.0f);
	m_EngineEffects = AddComponent<SESpriteComponent>();
	m_WeaponsFireEffects = AddComponent<SESpriteComponent>();


	GetSpriteComponent()->ClearSprites();

	GetSpriteComponent()->AddSingleSprite("EngineContent/Images/SpriteSheets/Enemies/Base/Kla'ed - Dreadnought - Base.png");

	SEAnimParams AnimParams;
	AnimParams.EndFrame = 11;
	AnimParams.FrameCount = 12;

	m_EngineEffects->AddAnimation(
		"EngineContent/Images/SpriteSheets/Enemies/EngineEffects/Kla'ed - Dreadnought - Engine - 11f.png",
		AnimParams);

	AnimParams.EndFrame = 59;
	AnimParams.FrameCount = 60;

	m_WeaponsFireEffects->AddAnimation(
		"EngineContent/Images/SpriteSheets/Enemies/Weapons/Kla'ed - Dreadnought - Weapons - 60f.png",
		AnimParams);

	m_Value = 500;
	m_Lives = 20;

	m_ShootTimer = 0.0f;
	m_FireRate = 8.0f;

	GetMovementComponent()->m_MaxVelocity = 12.5f;

}

void SEEnemyDreadnought::BeginPlay()
{
	SECharacter::BeginPlay();
	GetCollisionComponent()->GetCollision()->Bounds.w = GetScaledCharacterSize().x * 0.5;
	GetCollisionComponent()->GetCollision()->Bounds.h = GetScaledCharacterSize().y * 0.5;

	GetCollisionComponent()->BoundsOffset.x = 38.0f;
	GetCollisionComponent()->BoundsOffset.y = 48.0f;
	// GetCollisionComponent()->GetCollision()->Debug = true;
}

void SEEnemyDreadnought::Update(float DeltaTime)
{
	SEEnemy::Update(DeltaTime);
	TryShoot();


	if (m_ShootTimer < m_FireRate) {
		m_ShootTimer += DeltaTime;
	}
}

void SEEnemyDreadnought::TryShoot()
{
	if (m_ShootTimer >= m_FireRate) {
		m_ShootTimer = 0.0f;

		SEEnemyProjectileRay* Proj = Game::GetGameInstance()->AddGameObject<SEEnemyProjectileRay>();

		SEVector2 SpawnPos = (GetTransform()->Position + (GetScaledCharacterSize() * 0.5f));
		SpawnPos.x -= 69.0f;
		SpawnPos.y += 45.0f;
		Proj->SetPosition(SpawnPos);
	}
}