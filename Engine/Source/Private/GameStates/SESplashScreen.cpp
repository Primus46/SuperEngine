#include "CoreMinimal.h"
#include "GameStates/SESplashScreen.h"

#include "GameObjects/SETextObject.h"
#include "Window/Window.h"
#include "SEInput.h"
#include "GameStates/SEMainMenuState.h"
#include "Game.h"
#include "GameStates/SEGameStateMachine.h"

void SESplashScreen::OnBeginPlay()
{
	SETextObject* Title = AddGameObject<SETextObject>();
	SETextObject* SubTitle = AddGameObject<SETextObject>();

	Title->LoadFont("EngineContent/Fonts/Shojumaru/Shojumaru-Regular.ttf");
	Title->SetFontSize(144);
	Title->SetText("GAXALY");

	float HalfWidth = static_cast<float>(GetWindow()->GetWidth()) * 0.5f;
	float ThirdHeight = static_cast<float>(GetWindow()->GetHeight()) * 0.3f;

	Title->SetPosition({
		HalfWidth - Title->GetWidth() * 0.5f,
		ThirdHeight - Title->GetHeight() * 0.5f
		});

	SubTitle->LoadFont("EngineContent/Fonts/Shojumaru/Shojumaru-Regular.ttf");
	SubTitle->SetFontSize(40);
	SubTitle->SetText("Press Space bar to Enter Main Menu");

	float FifthHeight = static_cast<float>(GetWindow()->GetHeight()) * 0.5f;

	SubTitle->SetPosition({
		HalfWidth - SubTitle->GetWidth() * 0.5f,
		FifthHeight - SubTitle->GetHeight() * 0.5f
		});
}

void SESplashScreen::OnProcessInput(SEInput* GameInput)
{
	if (GameInput->IsKeyDown(SDL_SCANCODE_SPACE)) {
		Game::GetGameInstance()->GetGameStateMachine()->SetNewState<SEMainMenuState>();
	}
}
