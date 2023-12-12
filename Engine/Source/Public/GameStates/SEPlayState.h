#pragma once

#include "GameStates/SEGameState.h"

class SEPlayer;
class SETextObject;

class SEPlayState :
	public SEGameState
{
public:
	SEPlayState(Window* AssignedWindow);
	
	virtual void OnBeginPlay() override;

	virtual void OnProcessInput(SEInput* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;

protected:
	// spawn an enemy into a random position in the game
	void SpawnEnemy();

	// update the score if it's changed
	void UpdateScore();

	void UpdatePlayerLives();

	virtual void EndPlay() override;

private:
	// store the player game object if we need it
	SEPlayer* m_Player;

	// time before the next enemy spawn
	float m_SpawnTimer;

	// how long would it take before spawning an enemy
	float m_SpawnFrequency;

	// store the text object for the score
	SETextObject* m_ScoreText;

	// store the text object for the player lives
	SETextObject* m_PlayerLivesText;

	// this exists to test if the score has changed and needs updating
	int m_StateScore;

	int m_StatePlayerLives;
};

