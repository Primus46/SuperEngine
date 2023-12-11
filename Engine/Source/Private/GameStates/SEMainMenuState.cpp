#include "CoreMinimal.h"
#include "GameStates/SEMainMenuState.h"
#include "GameObjects/SETextObject.h"
#include "Window/Window.h"
#include "SEInput.h"
#include "GameStates/SEPlayState.h"
#include "Game.h"
#include "GameStates/SEGameStateMachine.h"

void SEMainMenuState::OnBeginPlay()
{
	SETextObject* Title = AddGameObject<SETextObject>();
	Title->LoadFont("EngineContent/images/Fonts/Pixelify/PixelifySans-Bold.ttf");
	Title->SetFontSize(60);
	Title->SetText("Press SPAC BAR to start Game.");

	float HalfWidth = static_cast<float>(GetWindow()->GetWidth()) * 0.5f;
	float HalfHeight = static_cast<float>(GetWindow()->GetHeight()) * 0.5f;

	Title->SetPosition({
		HalfWidth - Title->GetWidth() * 0.5f,
		HalfHeight - Title->GetHeight() * 0.5f
	});
}

void SEMainMenuState::OnProcessInput(SEInput* GameInput)
{
	if (GameInput->IsKeyDown(SDL_SCANCODE_SPACE)) {
		Game::GetGameInstance()->GetGameStateMachine()->SetNewState<SEPlayState>();
	}
}