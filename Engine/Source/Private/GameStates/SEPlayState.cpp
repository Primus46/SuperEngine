#include "CoreMinimal.h"
#include "GameStates/SEPlayState.h"

#include "GameObjects/Characters/SEEnemy.h"
#include "GameObjects/Characters/SEEnemyShooter.h"
#include "GameObjects/Characters/SEEnemyBattlecruiser.h"
#include "GameObjects/Characters/SEEnemyDreadnought.h"

#include "GameObjects/Characters/SEPlayer.h"
#include "Window/Window.h"
#include "SEInput.h"
#include "Game.h"
#include "GameStates/SEGameStateMachine.h"
#include "GameObjects/SETextObject.h"
#include "SEAudioPlayer.h"
#include "GameStates/SEMainMenuState.h"

#include "GameObjects/Projectiles/SEPlayerProjectile.h"

SEPlayState::SEPlayState(Window* AssignedWindow) 
	: SEGameState(AssignedWindow)
{
	m_Player = nullptr;
	m_SpawnTimer = 0.0f;
	m_SpawnFrequency = 8.0f;
	m_ScoreText = nullptr;
	m_StateScore = -1;
	m_StatePlayerLives = -1;
	m_PlayerLivesText = nullptr;
}

void SEPlayState::OnBeginPlay()
{
	// DEBUG add test game object
	srand(static_cast<SEUint>(time(NULL)));

	SpawnEnemy();

	m_Player = AddGameObject<SEPlayer>();

	m_Player->SetPosition({
		(static_cast<float>(GetWindow()->GetWidth()) * 0.5f) - m_Player->GetScaledCharacterSize().x,
		static_cast<float>(GetWindow()->GetHeight()) - m_Player->GetScaledCharacterSize().y
		});

	Game::GetGameInstance()->SetScore(0);

	m_ScoreText = AddGameObject<SETextObject>();
	m_ScoreText->LoadFont("EngineContent/Fonts/Pixelify/PixelifySans-Regular.ttf");
	m_ScoreText->SetFontSize(48);
	UpdateScore();

	m_PlayerLivesText = AddGameObject<SETextObject>();
	m_PlayerLivesText->LoadFont("EngineContent/Fonts/Pixelify/PixelifySans-Regular.ttf");
	m_PlayerLivesText->SetFontSize(36);


	Mix_Music* Music = GetAudio()->LoadMusic("EngineContent/Audio/321007__littlerobotsoundfactory__loop_nothing_can_stop_progress_01.wav");
	GetAudio()->PlayMusic(Music, 12);
}

void SEPlayState::OnProcessInput(SEInput* GameInput)
{
	static float SwitchTimer = 0.0f;

	if (GameInput->IsKeyDown(SDL_SCANCODE_1) && SwitchTimer <= 0.0f) {
		SwitchTimer = 1.0f;
		Game::GetGameInstance()->GetGameStateMachine()->SetNewState<SEPlayState>();
	}

	if (SwitchTimer > 0.0f) {
		SwitchTimer -= Game::GetGameInstance()->GetDeltaTimeF();
	}

}

void SEPlayState::OnUpdate(float DeltaTime)
{	

	UpdateScore();
	UpdatePlayerLives();
	// increment the timer every frame
	m_SpawnTimer += DeltaTime;

	// check if the timer is greater than or eqaul to the spawn frequency
	if (m_SpawnTimer >= m_SpawnFrequency) {
		// spawn the enemy and reset the timer
		SpawnEnemy();
		m_SpawnTimer = 0.0f;
		// increase the frequency over time
		m_SpawnFrequency -= 0.2f;
		// make sure the frequency can't go below 0.5s
		m_SpawnFrequency = std::max(1.0f, m_SpawnFrequency);
	}

	if (m_Player->GetLives() <= 0) {
		Game::GetGameInstance()->GetGameStateMachine()->SetNewState<SEMainMenuState>();
	}
}

void SEPlayState::SpawnEnemy()
{
	static float SwitchTimer = 0.0f;

	SEEnemy* Enemy;
	// change number depending on th eamount of enemies
	// selects with enemy type is spawned
	if (rand() % 3 == 0) {
		Enemy = AddGameObject<SEEnemyShooter>();
	}
	else if (rand() % 3 == 1) {
		Enemy = AddGameObject<SEEnemyBattlecruiser>();
	}
	else if (rand() % 3 == 2) {
		Enemy = AddGameObject<SEEnemyDreadnought>();
	}
	else {
		Enemy = AddGameObject<SEEnemy>();
	}

	float WindowLength = static_cast<float>(GetWindow()->GetWidth()) - Enemy->GetScaledCharacterSize().x;
	float RandomMax = static_cast<float>(RAND_MAX) / WindowLength;
	float RandomPos = static_cast<float>(rand()) / RandomMax;

	Enemy->SetPosition({	// set Enemy x position to middle of screen
		RandomPos,
		-Enemy->GetScaledCharacterSize().y
		});
}

void SEPlayState::UpdateScore()
{
	int GameScore = Game::GetGameInstance()->GetScore();

	if (m_StateScore == GameScore) {
		return;
	}

	float HalfWindowWidth = static_cast<float>(GetWindow()->GetWidth()) * 0.5f;

	m_ScoreText->SetText(std::to_string(GameScore));
	m_ScoreText->SetPosition({
		HalfWindowWidth - (m_ScoreText->GetWidth() * 0.5f),
		10.0f
		});

	m_StateScore = GameScore;
}

void SEPlayState::UpdatePlayerLives()
{
	if (m_Player == nullptr) {
		return;
	}

	if (m_StatePlayerLives == m_Player->GetLives()) {
		return;
	}

	m_PlayerLivesText->SetText(SEString("Lives: ") + std::to_string(m_Player->GetLives()));
	m_PlayerLivesText->SetPosition({ 10.0f, 10.0f });

	m_StatePlayerLives = m_Player->GetLives();
}

void SEPlayState::EndPlay()
{
	GetAudio()->PauseMusic();
}
