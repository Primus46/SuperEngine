#include "CoreMinimal.h"
#include "GameObjects/Characters/SEEnemy.h"
#include "GameObjects/Components/SESpriteComponent.h"
#include "GameObjects/Components/SEMovementComponent.h"
#include "GameObjects/Components/SECollisionComponent.h"
#include "Window/Window.h"
#include "Game.h"
#include "SEAudioPlayer.h"


SEEnemy::SEEnemy(SEString DefaultName, Window* AssignedWindow) 
	: SECharacter(DefaultName, AssignedWindow)
{
	GetCollisionComponent()->GetCollision()->Type = OT_ENEMY;

	m_CharacterSize = SEVector2(64.0f);
	m_EngineEffects = AddComponent<SESpriteComponent>();

	// add ship sprite to the main sprite component
	GetSpriteComponent()->AddSingleSprite("EngineContent/Images/SpriteSheets/Enemies/Base/Kla'ed - Fighter - Base.png");

	SEAnimParams AnimParams;
	AnimParams.EndFrame = 9;
	AnimParams.FrameCount = 10;
	
	m_EngineEffects->AddAnimation(
		"EngineContent/Images/SpriteSheets/Enemies/EngineEffects/Kla'ed - Fighter - Engine-10f.png",
		AnimParams);

	// moves down the screen from the get go
	m_MovementDir = SEVector2(0.0f, 1.0f);

	m_EnemyAcceleration = 100.0f;
	GetMovementComponent()->m_MaxVelocity = 100.0f;
	GetMovementComponent()->m_Drag = -5.0f;

	SetRotation(180.0f);
	SetScale(2.0f);

	m_DestroySFX[0] = GetAudio()->LoadSFX("EngineContent/Audio/Destroy_small_SFX_1.wav");
	m_DestroySFX[1] = GetAudio()->LoadSFX("EngineContent/Audio/Destroy_small_SFX_2.wav");
}

void SEEnemy::Update(float DeltaTime)
{
	SECharacter::Update(DeltaTime);
	
	GetMovementComponent()->AddForce(m_MovementDir, m_EnemyAcceleration);
	
	if (GetTransform()->Position.y > GetWindow()->GetHeight()) {
		Destroy();
		Game::GetGameInstance()->AddScore(-100);
	}

}

void SEEnemy::BeginPlay()
{
	SECharacter::BeginPlay();

	GetCollisionComponent()->GetCollision()->Bounds.w = GetScaledCharacterSize().x * 0.5;
	GetCollisionComponent()->GetCollision()->Bounds.h = GetScaledCharacterSize().y * 0.5;
	GetCollisionComponent()->BoundsOffset.x = 32.0f;
	GetCollisionComponent()->BoundsOffset.y = 22.0f;
}

void SEEnemy::DestroyWithEffects()
{
	int Rand = rand() % 2;

	GetAudio()->PlaySFX(m_DestroySFX[Rand], 100);

	Destroy();
}
