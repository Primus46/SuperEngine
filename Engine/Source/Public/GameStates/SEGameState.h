#pragma once

class SEInput;
class Window;
class SECollisionEngine;
class SEGameObject;
class SEAudioPlayer;

class SEGameState
{
public:
	SEGameState(Window* AssignedWindow);
	~SEGameState();

	// Runs whenever the game state starts
	void BeginPlay();

	// runs at the start of each loop
	void LoopStart();

	// Listens out for the input events
	void ProcessInput(SEInput* GameInput);

	// Runs logic at before rendering and after input
	void Update(float DeltaTime);

	// handle the deletion of objects at the end of the loop
	void CollectGarbage();

	// returns the collision engine for the current set game state
	SECollisionEngine* GetCollisionEngine() const { return m_CollisionEngine; }

	// get the window assigned to this game states
	Window* GetWindow() const { return m_Window; }

	// has the game state been marked for destroy
	bool IsPendingDestroy() const { return m_ShouldDestroy; }

	// mark the game state for destruction
	void destroy();

	// get game audio
	SEAudioPlayer* GetAudio() const;

	// add a game object to the game
	template<class G, typename std::enable_if<std::is_base_of<SEGameObject, G>::value>::type* = nullptr>
	G* AddGameObject(SEString ObjectName = "GameObject") {
		G* NewGameObject = new G(ObjectName, m_Window);

		if (NewGameObject == nullptr) {
			SELog("GameObject failed to create: " + ObjectName);
			return nullptr;
		}

		m_SpawnObjectStack.push_back(NewGameObject);

		return NewGameObject;
	}

	// runs when the game state gets swwitched out or destroyed
	virtual void EndPlay() {}

protected:
	// Runs whenever the game state starts
	// Makes sure that the begin play of game objects is run after this
	virtual void OnBeginPlay() {}
	
	// Listens out for the input events
	virtual void OnProcessInput(SEInput* GameInput) {}

	// Runs logic at before rendering and after input
	virtual void OnUpdate(float DeltaTime) {}

private:
	// Window assigned to the game state
	Window* m_Window;

	// store all of the collisions related to the game state
	SECollisionEngine* m_CollisionEngine;

	// hold all the game objects in the game
	TArray<SEGameObject*> m_GameObjectStack;

	// holds all the gameobjects waiting to spawn on the next loop
	TArray<SEGameObject*> m_SpawnObjectStack;

	// hold the flag of pending destroy
	bool m_ShouldDestroy;
};
