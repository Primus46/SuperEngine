#include "CoreMinimal.h"
#include "Game.h"
#include "Window/Window.h"
#include "SEInput.h"
#include "SDL2/SDL_ttf.h"

#include "GameStates/SEGameStateMachine.h"
#include "GameStates/SEGameState.h"
#include "GameStates/SEPlayState.h"
#include"GameStates/SEMainMenuState.h"


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
			LoopStart();

			ProcessInput();

			Update();

			Render();

			CollectGarbage();
		}
	}

	CleanupGame();
}

SECollisionEngine* Game::GetCollisions() const
{
	return m_GameStateMachine->GetActiveGameState()->GetCollisionEngine();
}

void Game::SetScore(int Score)
{
	m_GameScore = Score;
}

void Game::AddScore(int Amount)
{
	SetScore(GetScore() + Amount);
}

void Game::RestartGame()
{
	/*
	m_GameScore = 0;
	//Create a new state and this will automatically run the beginplay
	m_GameStateMachine->SetNewState<SEMainMenuState>();
	*/
}

Game::Game()
{
	std::cout << "Create Game." << std::endl;
	m_IsRunning = true;
	m_Window = nullptr;
	m_DeltaTime = 0.0;
	m_GameInput = nullptr;
	m_GameStateMachine = nullptr;
	m_GameScore = 0;
}

Game::~Game()
{
	std::cout << "Destroy Game." << std::endl;
}

bool Game::Initialise()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SELog("SDL failed to initialise: " + SEString(SDL_GetError()));
		return false;
	}
	if (TTF_Init() == -1) {
		SELog("SDL TTF failed to initialise: " + SEString(TTF_GetError()));
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

	// create the game state machine and add the assigned window
	m_GameStateMachine = new SEGameStateMachine(m_Window);
	//Create a new state and this will automatically run the beginplay
	m_GameStateMachine->SetNewState<SEMainMenuState>();

	m_GameStateMachine->BeginPlay();

	/*
	* Replace
	m_GameStateMachine->SetNewState<SEMainMenuState>();
	*With
	* RestartGame();
	*/
}

void Game::LoopStart()
{
	m_GameStateMachine->LoopStart();
}

void Game::ProcessInput()
{
	if (m_GameInput == nullptr) {
		SELog("No input class detected.");

		return;
	}
	// process the inputs and workout what hes been pressed
	m_GameInput->ProcessInput();

	// run the inputs detection for the game state
	m_GameStateMachine->ProcessInput(m_GameInput);
	
}

void Game::Update()
{
	// delta time must be calculated first
	static double LastTickTime = 0.0;
	// get the amount of time tht's passed since the game started from SDL_GetTicks
	double CurrentTickTime = static_cast<double>(SDL_GetTicks64());
	// remove the last tick from the current tick time to get the delta time
	// we also want to simplify the number to seconds so we divide it by 1000
	m_DeltaTime = (CurrentTickTime - LastTickTime) / 1000.0;
	// update the last tick time
	LastTickTime = CurrentTickTime;

	// on escape pressed end game
	if (m_GameInput->IsKeyDown(SDL_SCANCODE_ESCAPE)) {
		EndGame();
	}

	// runs the update logic for game state
	m_GameStateMachine->Update(GetDeltaTimeF());

	/*
	static float GameTimer = 0.0f;
	GameTimer += GetDeltaTimeF();

	if (GameTimer > 5.0f && m_Player != nullptr) {
		m_Player->Destroy();
		m_Player = nullptr;
	}
	*/
}

void Game::Render()
{
	m_Window->Render();
}

void Game::CollectGarbage()
{
	m_GameStateMachine->CollectGabage();
}

void Game::CleanupGame()
{
	// delete the current game state from memory
	delete m_GameStateMachine;
	// delete the input
	delete m_GameInput;

	// destroy and deallocate the window
	if (m_Window != nullptr) {
		m_Window->Destroy();
		delete m_Window;
	}
	// deload the TTF stuff
	TTF_Quit();

	// quit SDL
	SDL_Quit();
}
