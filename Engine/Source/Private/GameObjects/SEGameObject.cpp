#include "CoreMinimal.h"
#include "GameObjects/SEGameObject.h"
#include "GameObjects/Components/SEComponent.h"
#include "Game.h"

SEGameObject::SEGameObject(SEString DefaultName, Window* AssignedWindow)
	: m_Name(DefaultName), m_Window(AssignedWindow)
{
	m_Transform = AddComponent<SETransformComponent>();
}

void SEGameObject::BeginPlay()
{
	for (auto Component : m_Components) {
		if (Component == nullptr) {
			continue;
		}

		Component->BeginPlay();
	}
}

void SEGameObject::ProcessInput(SEInput* GameInput)
{
	for (auto Component : m_Components) {
		if (Component == nullptr) {
			continue;
		}

		Component->ProcessInput(GameInput);
	}
}

void SEGameObject::Update(float DeltaTime)
{
	for (auto Component : m_Components) {
		if (Component == nullptr) {
			continue;
		}

		Component->Update(DeltaTime);
	}

	 
}

void SEGameObject::Destroy()
{
	OnDestroy();

	for (auto Component : m_Components) {
		// test if the item is nullptr
		if (Component == nullptr) {
			// skip this loop if it is
			continue;
		}

		Component->Destroy();
	}

	// remove all references to memory in the array
	//because all components are shared ptrs they will delete themselves
	m_Components.clear();

	// let's the game know this game object wants to be removed
	m_ShouldDestroy = true;
}

void SEGameObject::SetPosition(SEVector2 Position)
{
	m_Transform->Position = Position;
}

void SEGameObject::SetScale(SEVector2 Scale)
{
	m_Transform->Scale = Scale;
}

void SEGameObject::SetRotation(float Rotation)
{
	m_Transform->Rotation = Rotation;
}

SEAudioPlayer* SEGameObject::GetAudio() const
{
	return Game::GetGameInstance()->GetAudio() ;
}
