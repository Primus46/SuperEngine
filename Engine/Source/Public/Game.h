#pragma once

class Window;
class SEInput;

//DEBUG
class SEAnimStateMachine;
class SEGameObject;

class Game {
public:
	static Game* GetGameInstance();
	static void DestroyGameInstance();

	void Run();

	inline void EndGame() { m_IsRunning = false; }

	inline float GetDeltaTimeF() const { return static_cast<float>(m_DeltaTime); }

	// add a game object to the game
	template<class G, typename std::enable_if<std::is_base_of<SEGameObject, G>::value>::type* = nullptr>
	inline TSharedPtr<G> AddGameObject(SEString ObjectName) {
		TSharedPtr<G> NewGameObject = TMakeShared<G>(ObjectName, m_Window);

		if (NewGameObject == nullptr) {
			SELog("GameObject failed to create: " + ObjectName);
			return nullptr;
		}

		m_GameObjectStack.push_back(NewGameObject);

		return NewGameObject;
	}

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
	// game flag loop
	bool m_IsRunning;
	// store the window
	Window* m_Window;
	// time between each tick/frame
	double m_DeltaTime;
	// store the game input
	SEInput* m_GameInput;

	// hold all the game objects in the game
	TSharedArray<SEGameObject> m_GameObjectStack;

};