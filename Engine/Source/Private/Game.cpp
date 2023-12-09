#include "CoreMinimal.h"
#include "Game.h"
#include "Window/Window.h"
#include "SEInput.h"
#include "Math/SEVector2.h"
#include "GameObjects/SEGameObject.h"

// DEBUG HEADER
#include "GameObjects/Characters/SEPlayer.h"
#include "GameObjects/Characters/SEEnemy.h"
#include "Collisions/SECollisionEngine.h"

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

void Game::RemoveGameObject(SEGameObject* GameObject)
{
	auto it = std::find(m_GameObjectStack.begin(),
		m_GameObjectStack.end(), 
		GameObject
	);

	// if it == end() then that means reached the empty item vector array and that means there is no item
	if (it == m_GameObjectStack.end()) {
		return;
	}

	// delete the game objects from memory
	delete *it;
	

	// erase removes items from the array
	m_GameObjectStack.erase(it);
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

	// DEBUG
	m_Player = nullptr;
	m_CollisionEngine = nullptr;

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
	m_CollisionEngine = new SECollisionEngine();

	// DEBUG add test game object
	SEEnemy* Enemy = AddGameObject<SEEnemy>();
	m_Player = AddGameObject<SEPlayer>();

	
	Enemy->SetPosition({ 
		static_cast<float>(Enemy->GetWindow()->GetWidth() * 0.5f) - 64.0f *2.0f, // set Enemy x position to middle of screen
		-64.0f * 2.0f
		});
	m_Player->SetPosition({
		(static_cast<float>(m_Player->GetWindow()->GetWidth()) *0.5f) - (48.0f * 2.0f), // set Player x position to middle of screen
		static_cast<float>(m_Player->GetWindow()->GetHeight()) - (58.0f * 2.0f) // set Player y position to middle of screen
		});

	// loop through all game objects in the game and run their begin play
	for (auto GameObject : m_GameObjectStack) {
		if (GameObject == nullptr) {
			continue;
		}

		GameObject->BeginPlay();
	}

	/*
	* Replace
	//Create a new state and this will automatically run the beginplay
	m_GameStateMachine->SetNewState<SEMainMenuState>();
	*With
	* RestartGame();
	*/
}

void Game::ProcessInput()
{
	if (m_GameInput == nullptr) {
		SELog("No input class detected.");

		return;
	}
	m_GameInput->ProcessInput();

	// loop through all game objects in the game and run their process input
	for (auto GameObject : m_GameObjectStack) {
		if (GameObject == nullptr) {
			continue;
		}

		GameObject->ProcessInput(m_GameInput);
	}
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

	// loop through all game objects in the game and run their begin update
	for (auto GameObject : m_GameObjectStack) {
		if (GameObject == nullptr) {
			continue;
		}

		GameObject->Update(GetDeltaTimeF());
	}

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

void Game::CleanupGame()
{
	// loop through all game objects in the game and run their destroy
	for (auto GameObject : m_GameObjectStack) {
		if (GameObject == nullptr) {
			continue;
		}

		GameObject->Destroy();
	}

	delete m_GameInput;

	if (m_Window != nullptr) {
		m_Window->Destroy();
		delete m_Window;
	}
	SDL_Quit();
}
