#include "CoreMinimal.h"
#include "GameObjects/Characters/SEEnemyBattlecruiser.h"

#include "GameObjects/Components/SESpriteComponent.h"
#include "GameObjects/Components/SECollisionComponent.h"
#include "GameObjects/Projectiles/SEEnemyProjectileMedium.h"
#include "Game.h"
#include "GameObjects/Components/SEMovementComponent.h"


SEEnemyBattlecruiser::SEEnemyBattlecruiser(SEString DefaultName, Window* AssignedWindow)
	:SEEnemy(DefaultName, AssignedWindow)
{
	m_CharacterSize = SEVector2(180.0f);
	m_EngineEffects = AddComponent<SESpriteComponent>();
	m_WeaponsFireEffects = AddComponent<SESpriteComponent>();


	GetSpriteComponent()->ClearSprites();

	GetSpriteComponent()->AddSingleSprite("EngineContent/Images/SpriteSheets/Enemies/Base/Kla'ed - Battlecruiser - Base.png");

	SEAnimParams AnimParams;
	AnimParams.EndFrame = 11;
	AnimParams.FrameCount = 12;

	m_EngineEffects->AddAnimation(
		"EngineContent/Images/SpriteSheets/Enemies/EngineEffects/Kla'ed - Battlecruiser - Engine - 12f.png",
		AnimParams);

	AnimParams.EndFrame = 29;
	AnimParams.FrameCount = 30;

	m_WeaponsFireEffects->AddAnimation(
		"EngineContent/Images/SpriteSheets/Enemies/Weapons/Kla'ed - Battlecruiser - Weapons - 30f.png",
		AnimParams);

	m_Value = 40;
	m_Lives = 5;

	m_ShootTimer = 0.0f;
	m_FireRate = 2.0f;

	GetMovementComponent()->m_MaxVelocity = 50.0f;

}

void SEEnemyBattlecruiser::BeginPlay()
{
	SECharacter::BeginPlay();
	GetCollisionComponent()->GetCollision()->Bounds.w = GetScaledCharacterSize().x * 0.5;
	GetCollisionComponent()->GetCollision()->Bounds.h = GetScaledCharacterSize().y * 0.5;

	GetCollisionComponent()->BoundsOffset.x = 38.0f;
	GetCollisionComponent()->BoundsOffset.y = 48.0f;
	// GetCollisionComponent()->GetCollision()->Debug = true;
}

void SEEnemyBattlecruiser::Update(float DeltaTime)
{
	SEEnemy::Update(DeltaTime);
	TryShoot();


	if (m_ShootTimer < m_FireRate) {
		m_ShootTimer += DeltaTime;
	}
}

void SEEnemyBattlecruiser::TryShoot()
{
	if (m_ShootTimer >= m_FireRate) {
		m_ShootTimer = 0.0f;

		SEEnemyProjectileMedium* Proj = Game::GetGameInstance()->AddGameObject<SEEnemyProjectileMedium>();

		SEVector2 SpawnPos = (GetTransform()->Position + (GetScaledCharacterSize() * 0.5f));
		SpawnPos.x -= 60.0f;
		SpawnPos.y += 40.0f;
		Proj->SetPosition(SpawnPos);
	}
}
