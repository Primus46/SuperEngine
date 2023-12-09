#pragma once

class SEGameObject;
class SEInput;

class SEComponent {
public:
	SEComponent(SEGameObject* Owner) : m_Owner(Owner) {}
	~SEComponent() = default;

	// Run when component first spawns
	virtual void BeginPlay() { ; }

	// Detect game Input
	virtual void ProcessInput(SEInput* GameInput) { ; }

	// Run component logic
	virtual void Update(float DeltaTime) { ; }

	// Destroys component
	void Destroy();

	// returns the game object owner of the component
	SEGameObject* GetOwner() const { return m_Owner; }

protected:
	virtual void OnDestroy() { ; }

private:
	//the gameObject owners of the component
	SEGameObject* m_Owner;
};