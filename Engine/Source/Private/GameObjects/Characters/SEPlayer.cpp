 #include "CoreMinimal.h"
#include "GameObjects/Characters/SEPlayer.h"

#include "GameObjects/Components/SEMovementComponent.h"
#include "GameObjects/Components/SESpriteComponent.h"
#include "GameObjects/Components/SECollisionComponent.h"
#include "SEInput.h"
#include "Window/Window.h"

SEPlayer::SEPlayer(SEString DefaultName, Window* AssignedWindow)
	: SECharacter(DefaultName, AssignedWindow)
{
	m_CharacterSize = SEVector2(48.0f, 58.0f);
	m_MainshipSprite = AddComponent<SESpriteComponent>();

	m_PlayerAcceleration = 100.0f;
	GetMovementComponent()->m_MaxVelocity = 600.0f;
	GetMovementComponent()->m_Drag = 1.0f;

	// add player sprites & animations

	m_MainshipSprite->AddSingleSprite("EngineContent/Images/SpriteSheets/MainShip/Base/player_1.png");
	m_MainshipSprite->AddSingleSprite("EngineContent/Images/SpriteSheets/MainShip/Base/player_2.png");
	m_MainshipSprite->AddSingleSprite("EngineContent/Images/SpriteSheets/MainShip/Base/player_3.png");

	SEAnimParams AnimParams;
	
	AnimParams.FrameCount = 3;
	AnimParams.EndFrame = 2;
	AnimParams.RowCount = 3;

	// animation for Player ship left & right



	// animation for Player ship foward & back
	m_MainshipSprite->AddAnimation(
		"EngineContent/Images/SpriteSheets/MainShip/spritesheet_player_9f.png",
		AnimParams);



	SetScale(2.0f);
}

void SEPlayer::BeginPlay()
{
	SECharacter::BeginPlay();

	GetCollisionComponent()->GetCollision()->Bounds.w = GetScaledCharacterSize().x * 1.0;
	GetCollisionComponent()->GetCollision()->Bounds.h = GetScaledCharacterSize().y * 0.9;
	GetCollisionComponent()->BoundsOffset.x = 0.0f;
	GetCollisionComponent()->BoundsOffset.y = 5.0f;
}

void SEPlayer::Update(float DeltaTime)
{
	SECharacter::Update(DeltaTime);


	GetMovementComponent()->AddForce(m_MovementDir, m_PlayerAcceleration);

	// is velocity  if the movemnet component greater than 0 - are we moving? 
	if (GetMovementComponent()->GetVelocity().Length() > 500.0f) {
		m_MainshipSprite->SetSpriteIndex(3); // Powered loop
	}
	else {
		if (GetMovementComponent()->GetVelocity().Length() > 200.0f &&
			GetMovementComponent()->GetVelocity().Length() < 500.0f) {
			m_MainshipSprite->SetSpriteIndex(2); // powering up or down
		}
		else if (GetMovementComponent()->GetVelocity().Length() > 10.0f &&
			GetMovementComponent()->GetVelocity().Length() < 200.0f) {
			m_MainshipSprite->SetSpriteIndex(1); // powering up or down
		}
		else {
			m_MainshipSprite->SetSpriteIndex(0); // idle
		}
	}
	
	

	LimitPlayerX();
}

void SEPlayer::ProcessInput(SEInput* GameInput)
{
	SECharacter::ProcessInput(GameInput);
	// reset input direction to update the correct direction
	// this will also make sure we have no input direction when not pressing anything
	m_MovementDir = SEVector2::Zero();

	// move up when pressing W
	if (GameInput->IsKeyDown(SDL_SCANCODE_W)) {
		m_MovementDir += SEVector2(0.0f, -1.0f);
	}
	// move down when pressing S
	if (GameInput->IsKeyDown(SDL_SCANCODE_S)) {
		m_MovementDir += SEVector2(0.0f, 1.0f);
	}
	// move right when pressing D
	if (GameInput->IsKeyDown(SDL_SCANCODE_D)) {
		m_MovementDir += SEVector2(1.0f, 0.0f);
	}
	// move left when pressing A
	if (GameInput->IsKeyDown(SDL_SCANCODE_A)) {
		m_MovementDir += SEVector2(-1.0f, 0.0f);
	}
}

void SEPlayer::OnBeginOverlap(SECollision* Col)
{
	SECharacter::OnBeginOverlap(Col);

	SELog("Collision Overlapped");
}

void SEPlayer::OnEndOverlap(SECollision* Col)
{
	SECharacter::OnEndOverlap(Col);

	SELog("Collision End Overlapped");
}

void SEPlayer::LimitPlayerX()
{
	// getting the width of the window and casting it to a float
	float WindowWidth = static_cast<float>(GetWindow()->GetWidth());
	//float WindowHeight = static_cast<float>(GetWindow()->GetHeight());

	float PlayerSizeWindowWidth = WindowWidth - GetScaledCharacterSize().x;
	//float PlayerSizeWindowHeight = WindowHeight - 58.0f * GetTransform()->Scale.y;

	// limit player movement left side of screen
	if (GetTransform()->Position.x <= 0.0f) {
		SetPosition({ 0.0f, GetTransform()->Position.y });
	}
	// limit player movement right side of screen
	if (GetTransform()->Position.x >= PlayerSizeWindowWidth) {
		SetPosition({ PlayerSizeWindowWidth, GetTransform()->Position.y });
	}
	/*// limit player movement top side of screen
	if (GetTransform()->Position.y <= 0.0f) {
		SetPosition({ 0.0f, GetTransform()->Position.x });
	}
	// limit player movement bottom side of screen
	if (GetTransform()->Position.y >= PlayerSizeWindowHeight) {
		SetPosition({ PlayerSizeWindowHeight, GetTransform()->Position.x });
	}*/
}
