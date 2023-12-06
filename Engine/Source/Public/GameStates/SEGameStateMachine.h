#pragma once
/*
class Window;
class SEGameState;
class SEInput;

class SEGameStateMachine
{
public:
	SEGameStateMachine(Window* AssignedWindow) : m_Window(AssignedWindow) {}
	~SEGameStateMachine();

	SEGameState* GetActiveGameState() const { return m_ActiveGameState; }

	void BeginPlay();

	void Update(float DeltaTime);

	void ProcessInput(SEInput* GameInput);

	void CollectGabage();

	// add or swap out a new game state
	template<class T, typename std::enable_if<std::is_base_of_v<SEGameState, T>>::type* = nullptr>
	T* SetNewState() {
		if (m_Window == nullptr) {
			SELog("Can't add game state, no window found.");
			return nullptr;
		}
		T* NewGameState = new T(m_Window);

		if (NewGameState == nullptr) {
			SELog("Failed to create Game State.");
			return nullptr;
		}
		SetActiveGameState; //  code missed here

		return NewGameState;
	}

protected:
	void SetActiveGameState(SEGameState* GameState);

private:
	Window* m_Window;

	SEGameState* m_ActiveGameState;
};

*/