#pragma once

#include "GameStates/SEGameState.h"
#include "GameStates/SEGameStateMachine.h"

class Window;
class SEInput;
class SECollisionEngine;
class SEGameStateMachine;
class SEAudioPlayer;


class Game {
public:
	static Game* GetGameInstance();
	static void DestroyGameInstance();

	void Run();

	/*inline*/ void EndGame() { m_IsRunning = false; }

	/*inline*/ float GetDeltaTimeF() const { return static_cast<float>(m_DeltaTime); }


	// gets the current collision engine
	SECollisionEngine* GetCollisions() const; 

	// returns the game state machine
	SEGameStateMachine* GetGameStateMachine() const { return m_GameStateMachine; }

	// get the score for the game
	int GetScore() const { return m_GameScore; }

	// set the score directly
	void SetScore(int Score);

	// add to the score
	void AddScore(int Amount);

	// Get the main Window
	Window* GetWindow() const { return m_Window; }

	//Restart the game back to the main menu
	void RestartGame();

	// get the audio player for the game
	SEAudioPlayer* GetAudio() const { return m_Audio; }

	// add a game object to the game
	template<class G, typename std::enable_if<std::is_base_of<SEGameObject, G>::value>::type* = nullptr>
	G* AddGameObject(SEString ObjectName = "GameObject") {
		return m_GameStateMachine->GetActiveGameState()->AddGameObject<G>(ObjectName);
	}
	 
private:
	Game();
	~Game();

	// initialise all libraries and dependencies
	bool Initialise();

	// runs once when the game starts
	// runs after initialise
	void Start();

	// runs at the start of each frame loop
	void LoopStart();

	// process any user input - first function in the game loop
	void ProcessInput();
	// update logic of the game based on input and checks - second function in the game loop
	void Update();
	// render graphics to the screen - third function in the game loop
	void Render();

	// handle garbage collection
	void CollectGarbage();

	//clears the game up (deallocates memory)
	void CleanupGame();

private:
	// game flag loop
	bool m_IsRunning;
	// store the window
	Window* m_Window;
	// time between each tick/frame
	double m_DeltaTime;
	// store the game input
	SEInput* m_GameInput;
	
	// store the game state machine
	SEGameStateMachine* m_GameStateMachine;
	
	// store the score for the game
	int m_GameScore;

	// store the audio player for the game
	SEAudioPlayer* m_Audio;

};