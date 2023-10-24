#pragma once

class Window;
class SEInput;
//DEBUG
class SEAnimation;
class SEGameObjects;

class Game {
public:
	static Game* GetGameInstance();
	static void DestroyGameInstance();

	void Run();

	inline void EndGame() { m_IsRunning = false; }

	inline float GetDeltaTimeF() const { return static_cast<float>(m_DeltaTime); }

private:
	Game();
	~Game();

	bool Initialise();
	void Start();

	// Game loop
	void ProcessInput();
	void Update();
	void Render();

	//clears the game up (deallocates memory)
	void CleanupGame();

private:
	bool m_IsRunning;

	Window* m_Window;
	
	double m_DeltaTime;

	SEInput* m_GameInput;

	// Dedug Variables - week 3
	SEAnimation* m_Anim;
	SEAnimation* m_Anim2;
	SEAnimation* m_Anim3;
	SEAnimation* m_Anim4;
	SEAnimation* m_Anim5;
	SEAnimation* m_Anim6;
	SEAnimation* m_Anim7;

	// Dedug Variables - week 5
	SEGameObjects* m_GameObject;
};