#include "CoreMinimal.h"
#include "Game.h"
#include "Window/Window.h"
#include "SEInput.h"
#include "Math/SEVector2.h"
//DEBUG INCLUDES -----
#include "Graphics/SETexture.h"
#include "Graphics/SEAnimation.h"
Game* Game::GetGameInstance()
{
	static Game* GameInstance = new Game();
	return GameInstance;
}

void Game::DestroyGameInstance()
{
	delete GetGameInstance();
}

void Game::Run()
{
	std::cout << "Run Game." << std::endl;

	m_IsRunning = Initialise();

	if (m_IsRunning) {
		Start();

		while (m_IsRunning) {
			ProcessInput();

			Update();

			Render();
		}
	}

	CleanupGame();
}

Game::Game()
{
	std::cout << "Create Game." << std::endl;
	m_IsRunning = true;
	m_Window = nullptr;
	m_DeltaTime = 0.0;
	m_GameInput = nullptr;

	//debug
	m_Anim = nullptr;
	m_Anim2 = nullptr;
}

Game::~Game()
{
	std::cout << "Destroy Game." << std::endl;
}

bool Game::Initialise()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL failed to initialise: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Game::Start()
{
	m_Window = new Window();

	if (!m_Window->CreateWindow("Super Engine", 1280, 720)) {
		EndGame();
		return;
	}
	m_GameInput = new SEInput();

	TSharedPtr<SETexture> Sprite1 = m_Window->CreateTexture("EngineContent/Images/Letters/HRed.png");

		if (Sprite1 != nullptr) {
			Sprite1->SetPosition(0.0f, 300.0f);
		}
	
	TSharedPtr<SETexture> Sprite2 = m_Window->CreateTexture("EngineContent/Images/Letters/EBlue.png");

		if (Sprite2 != nullptr) {
			Sprite2->SetPosition(120.0f, 300.0f);
		}

	m_Anim = new SEAnimation();
	m_Anim2 = new SEAnimation();
	m_Anim3 = new SEAnimation();
	m_Anim4 = new SEAnimation();
	m_Anim5 = new SEAnimation();
	m_Anim6 = new SEAnimation();
	m_Anim7 = new SEAnimation();

	SEAnimParams AnimParams;
	AnimParams.FrameCount = 10;
	AnimParams.EndFrame = 9;
	AnimParams.FrameRate = 18.0f;
	m_Anim->InportAnimation(m_Window, "EngineContent/Images/SpriteSheets/MainShip/Projectile-Green-10f.png", AnimParams);
	m_Anim->SetScale(4.0f, 4.0f);
	m_Anim->SetPosition(150.0f, 50.0f);

	AnimParams.FrameCount = 4;
	AnimParams.EndFrame = 3;

	m_Anim2->InportAnimation(m_Window, "EngineContent/Images/SpriteSheets/MainShip/Projectile-cannon-4f.png", AnimParams);
	m_Anim2->SetScale(4.0f, 4.0f);
	m_Anim2->SetPosition(50.0f, 50.0f);

	AnimParams.FrameCount = 10;
	AnimParams.EndFrame = 9;

	m_Anim3->InportAnimation(m_Window, "EngineContent/Images/SpriteSheets/Knight/_AttackComboNoMovement-10f.png", AnimParams);
	m_Anim3->SetScale(4.0f, 4.0f);
	m_Anim3->SetPosition(300.0f, 300.0f);

	AnimParams.FrameCount = 10;
	AnimParams.EndFrame = 9;

	m_Anim4->InportAnimation(m_Window, "EngineContent/Images/SpriteSheets/Knight/_Run-10f.png", AnimParams);
	m_Anim4->SetScale(4.0f, 4.0f);
	m_Anim4->SetPosition(300.0f, 50.0f);

	AnimParams.FrameCount = 7;
	AnimParams.EndFrame = 6;

	m_Anim5->InportAnimation(m_Window, "EngineContent/Images/SpriteSheets/Knight/_WallClimb-7f.png", AnimParams);
	m_Anim5->SetScale(4.0f, 4.0f);
	m_Anim5->SetPosition(750.0f, 50.0f);

	AnimParams.FrameCount = 12;
	AnimParams.EndFrame = 11;

	m_Anim6->InportAnimation(m_Window, "EngineContent/Images/SpriteSheets/Knight/_Roll-12f.png", AnimParams);
	m_Anim6->SetScale(4.0f, 4.0f);
	m_Anim6->SetPosition(750.0f, 300.0f);

	AnimParams.FrameCount = 10;
	AnimParams.EndFrame = 9;

	m_Anim7->InportAnimation(m_Window, "EngineContent/Images/SpriteSheets/Knight/_Death-10f.png", AnimParams);
	m_Anim7->SetScale(4.0f, 4.0f);
	m_Anim7->SetPosition(20.0f, 300.0f);
}

void Game::ProcessInput()
{
	if (m_GameInput == nullptr) {
		SELog("No input class detected.");

		return;
	}
	m_GameInput->ProcessInput();
}

void Game::Update()
{
	static double LastTickTime = 0.0;
	
	double CurrentTickTime = static_cast<double>(SDL_GetTicks64());

	m_DeltaTime = (CurrentTickTime - LastTickTime) / 1000.0;

	LastTickTime = CurrentTickTime;

	if (m_GameInput->IsKeyDown(SDL_SCANCODE_ESCAPE)) {
		EndGame();
	}

	SEVector2 MovementInput;
	static SEVector2 Position = SEVector2(50.0f);
	float speed = 500.0f * GetDeltaTimeF();

		/*if (m_GameInput->IsKeyDown(SDL_SCANCODE_D)) {
			MovementInput = SEVector2(1.0f, 0.0f);
		}
		if (m_GameInput->IsKeyDown(SDL_SCANCODE_A)) {
			MovementInput = SEVector2(-1.0f, 0.0f);
		}
		if (m_GameInput->IsKeyDown(SDL_SCANCODE_W)) {
			MovementInput = SEVector2(0.0f, -1.0f);
		}
		if (m_GameInput->IsKeyDown(SDL_SCANCODE_S)) {
			MovementInput = SEVector2(0.0f, 1.0f);
		}
		if(m_GameInput->IsMouseButttonDown(MB_LEFT)){
			m_ASH->SetIndex(1);
		}
		else{
			m_ASH->SetIndex(0);
		}

		MovementInput.LogLength();
		Position += MovementInput * 5.0f;
		m_ASM->SetPosition(Position.X, Position.Y);*/

	m_Anim->Update(GetDeltaTimeF());
	m_Anim2->Update(GetDeltaTimeF());
	m_Anim3->Update(GetDeltaTimeF());
	m_Anim4->Update(GetDeltaTimeF());
	m_Anim5->Update(GetDeltaTimeF());
	m_Anim6->Update(GetDeltaTimeF());
	m_Anim7->Update(GetDeltaTimeF());

}

void Game::Render()
{
	m_Window->Render();
}

void Game::CleanupGame()
{
	delete m_GameInput;

	if (m_Window != nullptr) {
		m_Window->Destroy();
		delete m_Window;
	}
	SDL_Quit();
}
