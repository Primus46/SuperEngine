#pragma once

class Window;
class SEGameState;
class SEInput;

class SEGameStateMachine
{
public:
	SEGameStateMachine(Window* AssignedWindow) 
		: m_Window(AssignedWindow), m_ActiveGameState(nullptr), m_StackedGameState(nullptr) {}
	~SEGameStateMachine();

	SEGameState* GetActiveGameState() const { return m_ActiveGameState; }

	void BeginPlay();

	void LoopStart();

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

		// create a game state of the type we input to the function
		// SetNewState<SEGameState>();
		T* NewGameState = new T(m_Window);

		if (NewGameState == nullptr) {
			SELog("Failed to create Game State.");
			return nullptr;
		}
		// assign the new game state to the current active game state                                        
		if (GetActiveGameState() == nullptr) {
			SetActiveGameState(NewGameState);
		}
		else {
			SwapGameState(NewGameState);
		}

		// return the result
		return NewGameState;
	}

protected:
	// sets the active game state and runs the begin play
	void SetActiveGameState(SEGameState* GameState);

	// destroy the game state and setup the next state
	void SwapGameState(SEGameState* NextState);

private:
	// store the window this game state machine is assigned to
	Window* m_Window;

	// current active game state
	SEGameState* m_ActiveGameState;

	// store the game state that will replace the current state
	SEGameState* m_StackedGameState;
};
