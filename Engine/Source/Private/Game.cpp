#include "CoreMinimal.h"
#include "Game.h"
#include "Window/Window.h"
#include "SEInput.h"
#include "Math/SEVector2.h"
#include "GameObjects/SEGameObjects.h"


//DEBUG INCLUDES -----
#include "Graphics/SETexture.h"
#include "Graphics/SEAnimation.h"
#include "Graphics/SEAnimStateMachine.h"
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
	m_ASM = nullptr;
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

	m_ASM = new SEAnimStateMachine();

	SEAnimParams AnimParams;
	AnimParams.FrameCount = 10;
	AnimParams.EndFrame = 9;
	AnimParams.FrameRate = 18.0f;
	m_ASM->AddAnimation(m_Window, "EngineContent/Images/SpriteSheets/MainShip/Projectile-Green-10f.png", AnimParams);

	AnimParams.FrameCount = 4;
	AnimParams.EndFrame = 3;

	m_ASM->AddAnimation(m_Window, "EngineContent/Images/SpriteSheets/MainShip/Projectile-cannon-4f.png", AnimParams);
	
	m_ASM->SetPosition(100.0f, 100.0f);
	m_ASM->SetScale(5.0f, 5.0f);

	m_ASM->Start();

	m_GameObject = new SEGameObjects("TestObject", m_Window);
	m_GameObject->BeginPlay();
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

	// on escape pressed end game
	if (m_GameInput->IsKeyDown(SDL_SCANCODE_ESCAPE)) {
		EndGame();
	}

	// refreshing the input each frame in case it changes
	SEVector2 MovementInput;
	// setting a static position on the first frame
	static SEVector2 Position = SEVector2(50.0f);
	// setting a speed so we can move based on time using delta time
	float Speed = 500.0f * GetDeltaTimeF();
	
	// move the input vector based on the keyboard input
		if (m_GameInput->IsKeyDown(SDL_SCANCODE_D)) {
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

		// changes the animation based on mouse input
		if(m_GameInput->IsMouseButtonDown(MB_LEFT)){
			m_ASM->SetIndex(1);
		}
		else{
			m_ASM->SetIndex(0);
		}

		// normalising the input so we don't go faster when holding 2 inputs
		MovementInput.Normalise();
		// adjusting our position based on speed
		Position += MovementInput * Speed;
		// setting the anim state machines position
		m_ASM->SetPosition(Position.x, Position.y);

		// updates the timing in the anim state machine
	m_ASM->Update(GetDeltaTimeF());
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
