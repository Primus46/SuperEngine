#pragma once

class Window;
class SEInput;
class SECollisionEngine;

//DEBUG
class SEAnimStateMachine;
class SEGameObject;


class Game {
public:
	static Game* GetGameInstance();
	static void DestroyGameInstance();

	void Run();

	/*inline*/ void EndGame() { m_IsRunning = false; }

	/*inline*/ float GetDeltaTimeF() const { return static_cast<float>(m_DeltaTime); }

	// add a game object to the game
	template<class G, typename std::enable_if<std::is_base_of<SEGameObject, G>::value>::type* = nullptr>
	inline G* AddGameObject(SEString ObjectName = "DefaultName") {
		G* NewGameObject = new G(ObjectName, m_Window);

		if (NewGameObject == nullptr) {
			SELog("GameObject failed to create: " + ObjectName);
			return nullptr;
		}

		m_GameObjectStack.push_back(NewGameObject);

		return NewGameObject;
	}

	// remove the game object from teh game objects stack
	// make sure to remove all references of the gameobject in other areas
	void RemoveGameObject(SEGameObject* GameObject);

	// gets the current collision engine
	SECollisionEngine* GetCollisions() const { return m_CollisionEngine; }

	// GEt the main Window
	Window* GetWindow() const { return m_Window; }

	//Restart the game back to the main menu
	void RestartGame();

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
	TArray<SEGameObject*> m_GameObjectStack;

	// DEBUG VAR
	SEGameObject* m_Player;

	// storing a collision engine in the game
	SECollisionEngine* m_CollisionEngine;
};