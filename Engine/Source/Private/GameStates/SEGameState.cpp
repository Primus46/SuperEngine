#include "CoreMinimal.h"
#include "GameStates/SEGameState.h"

#include "Collisions/SECollisionEngine.h"
#include "GameObjects/SEGameObject.h"


SEGameState::SEGameState(Window* AssignedWindow)
{
	m_Window = AssignedWindow;
	m_CollisionEngine = new SECollisionEngine();
	m_ShouldDestroy = false;
}

SEGameState::~SEGameState()
{
	for (auto GameObject : m_SpawnObjectStack) {
		GameObject->Destroy();
		delete GameObject;
	}

	m_SpawnObjectStack.clear();

	// delete all of the game objects from memory
	for (auto GameObject : m_GameObjectStack) {
		GameObject->Destroy();
		delete GameObject;
	}

	// resize the stack to 0
	m_GameObjectStack.clear();

	// clean up the collision egine
	delete m_CollisionEngine;
}

void SEGameState::BeginPlay()
{
	OnBeginPlay();
}

void SEGameState::LoopStart()
{
	if (m_SpawnObjectStack.size() <= 0) {
		return;
	}
	for (auto GameObject : m_SpawnObjectStack) {
		m_GameObjectStack.push_back(GameObject);
		GameObject->BeginPlay();
	}
	
	m_SpawnObjectStack.clear();
}

void SEGameState::ProcessInput(SEInput* GameInput)
{
	OnProcessInput(GameInput);

	// loop through all game objects in the game and run their process input
 	for (auto GameObject : m_GameObjectStack) {
		if (GameObject == nullptr) {
			continue;
		}

		GameObject->ProcessInput(GameInput);
	}
}

void SEGameState::Update(float DeltaTime)
{
	OnUpdate(DeltaTime);

	// loop through all game objects in the game and run their begin update
	for (auto GameObject : m_GameObjectStack) {
		if (GameObject == nullptr) {
			continue;
		}

		GameObject->Update(DeltaTime);
	}
}

void SEGameState::CollectGarbage()
{
	// loop through all the game objects and delete any that are marked
	for (auto it = m_GameObjectStack.begin(); it != m_GameObjectStack.end();) {
		// if there is a gameobject marked for destroy
		if ((*it)->IsPendingDestroy()) {
			// delete from memory
			delete* it;
			// we remove from the array
			// and update the iterator with one that wont break the for loop
			it = m_GameObjectStack.erase(it);
			// continue so that we don't change the new iterator
			continue;
		}

		++it;
	}
}

void SEGameState::destroy()
{
	m_ShouldDestroy = true;
}


