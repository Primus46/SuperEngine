#include "CoreMinimal.h"
#include "GameObjects/SEGameObjects.h"
#include "GameObjects/Components/SEComponents.h"

SEGameObjects::SEGameObjects(SEString DefaultName, Window* AssignedWindow)
	: m_Name(DefaultName), m_Window(AssignedWindow)
{
	AddComponents<SEComponents>();
}

void SEGameObjects::BeginPlay()
{
	for (auto Component : m_Components) {
		if (Component == nullptr) {
			continue;
		}

		Component->BeginPlay();
	}
}

void SEGameObjects::ProcessInput(SEInput* GameInput)
{
	for (auto Component : m_Components) {
		if (Component == nullptr) {
			continue;
		}

		Component->ProcessInput(GameInput);
	}
}

void SEGameObjects::Update(float DeltaTime)
{
	for (auto Component : m_Components) {
		if (Component == nullptr) {
			continue;
		}

		Component->Update(DeltaTime);
	}
}

void SEGameObjects::Destroy()
{
	OnDestroy();

	for (auto Component : m_Components) {
		if (Component == nullptr) {
			continue;
		}

		Component->Destroy();
	}

	m_Components.clear();

}
