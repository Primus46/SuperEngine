#pragma once

class Window;
class SEInput;
class SEComponents;

class SEGameObjects {
	SEGameObjects(SEString DefaultName, Window* AssignedWindow);
	~SEGameObjects() = default;

	// runs when the objects gets spawned into the game
	virtual void BeginPlay();

	// Listen for our input
	virtual void ProcessInput(SEInput* GameInput);

	// Update logic for the game object
	virtual void Update(float DeltaTime);

	// Destroys the object and it's components
	void Destroy();

protected:
	// Runs when the object is destroyed and before the components are destroyed
	virtual void OnDestroy() {}

	template <class T, typename std::enable_if<std::is_base_of<SEComponents, T>:: value>::type* = nullptr>
	inline TSharedPtr<T> AddComponents() {
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
	TSharedArray<SEComponents> m_Components;
};
