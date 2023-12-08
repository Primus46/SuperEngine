#pragma once

#include "GameObjects/Components/SETransformComponent.h"

class Window;
class SEInput;
class SEComponent;
class SETransformComponent;
struct SEVector2;

class SEGameObject {
public:
	SEGameObject(SEString DefaultName, Window* AssignedWindow);
	~SEGameObject() = default;

	// runs when the objects gets spawned into the game
	virtual void BeginPlay();

	// Listen for our input
	virtual void ProcessInput(SEInput* GameInput);

	// Update logic for the game object
	virtual void Update(float DeltaTime);

	// Destroys the object and it's components
	void Destroy();
	// Sets the position of the game object
	void SetPosition(SEVector2 Position);
	// Sets the Scale of the entire game object
	void SetScale(SEVector2 Scale);
	// Set the Rotation of the entire game object
	void SetRotation(float Rotation);
	// get the transform component
	TSharedPtr<SETransformComponent> GetTransform() const { return m_Transform; }

	// get the window the gameobject is assigned to
	Window* GetWindow() const { return m_Window; }

	// if destroyed wait for garbage collection
	bool IsPendingDestroy() const { return m_ShouldDestroy; }

protected:
	// Runs when the object is destroyed and before the components are destroyed
	virtual void OnDestroy() {}

	template <class T, typename std::enable_if<std::is_base_of<SEComponent, T>:: value>::type* = nullptr>
	inline TSharedPtr<T> AddComponent() {
		TSharedPtr<T> NewComponent = TMakeShared<T>(this);

		if (NewComponent == nullptr) {
			SELog("Failed to create component on: " + m_Name);
			return nullptr;
		}

		m_Components.push_back(NewComponent);

		return NewComponent;
	}

private:
	//Objects Unique Identifier
	SEString m_Name;

	//Window that this Object can renders to
	Window* m_Window;

	// all of the components assigned to the game object
	TSharedArray<SEComponent> m_Components;

	// holds the transform information for the game object
	TSharedPtr<SETransformComponent> m_Transform;

	// flag that the game object should be destroyed
	bool m_ShouldDestroy;
};
