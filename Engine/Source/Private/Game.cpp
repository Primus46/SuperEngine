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
		Sprite1->SetPosition(150.0f, 300.0f);
	}
	
	TSharedPtr<SETexture> Sprite2 = m_Window->CreateTexture("EngineContent/Images/Letters/EBlue.png");

		if (Sprite2 != nullptr) {
			Sprite2->SetPosition(350.0f, 300.0f);
		}

	m_Anim = new SEAnimation();
	m_Anim2 = new SEAnimation();

	SEAnimParams AnimParams;
	AnimParams.FrameCount = 10;
	AnimParams.EndFrame = 9;
	AnimParams.FrameRate = 12.0f;
	m_Anim->InportAnimation(m_Window, "EngineContent/Images/SpriteSheets/MainShip/Projectile-Green-10f.png", AnimParams);
	m_Anim->SetScale(6.0f, 6.0f);
	m_Anim->SetPosition(500.0f, 250.0f);

	AnimParams.FrameCount = 4;
	AnimParams.EndFrame = 3;

	m_Anim2->InportAnimation(m_Window, "EngineContent/Images/SpriteSheets/MainShip/Projectile-cannon-4f.png", AnimParams);
	m_Anim->SetScale(5.0f, 5.0f);
	m_Anim->SetPosition(250.0f, 250.0f);
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
