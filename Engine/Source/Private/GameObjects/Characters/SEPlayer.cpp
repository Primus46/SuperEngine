 #include "CoreMinimal.h"
#include "GameObjects/Characters/SEPlayer.h"

#include "GameObjects/Components/SEMovementComponent.h"
#include "SEInput.h"

SEPlayer::SEPlayer(SEString DefaultName, Window* AssignedWindow)
	: SECharacter(DefaultName, AssignedWindow)
{
	m_PlayerSpeed = 1000.0f;
	GetMovementComponent()->m_MaxVelocity = 5.0f;
	GetMovementComponent()->m_Drag = 10.0f;

	SetScale(3.0f);
}

void SEPlayer::Update(float DeltaTime)
{
	SECharacter::Update(DeltaTime);
	m_MovementDir.Log();

	GetMovementComponent()->AddForce(m_MovementDir, m_PlayerSpeed);
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
