#include "CoreMinimal.h"
#include "GameObjects/SEGameObject.h"
#include "GameObjects/Components/SEComponent.h"

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
		if (Component == nullptr) {
			continue;
		}

		Component->Destroy();
	}

	m_Components.clear();

}

void SEGameObject::SetPosition(SEVector2 Position)
{
	m_Transform->Position = Position;
}

void SEGameObject::SetScale(SEVector2 Scale)
{
	m_Transform->Scale = Scale;
}

void SEGameObject::SetRotation(SEVector2 Rotation)
{
	m_Transform->Rotation = Rotation;
}
