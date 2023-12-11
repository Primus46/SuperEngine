#include "CoreMinimal.h"
#include "GameStates/SEGameStateMachine.h"

#include "GameStates/SEGameState.h"


SEGameStateMachine::~SEGameStateMachine()
{
	delete m_ActiveGameState;

	if (m_StackedGameState != nullptr) {
		delete m_StackedGameState;
	}
}

void SEGameStateMachine::BeginPlay()
{
	if (GetActiveGameState() == nullptr) {
		SELog("No active game state assigned to the the state machine");
		SetNewState<SEGameState>();
		return;
	}
}

void SEGameStateMachine::LoopStart()
{
	if (GetActiveGameState() == nullptr) {
		return;
	}

	GetActiveGameState()->LoopStart();
}

void SEGameStateMachine::Update(float DeltaTime)
{
	if (GetActiveGameState() == nullptr) {
		return;
	}

	GetActiveGameState()->Update(DeltaTime);
}


void SEGameStateMachine::ProcessInput(SEInput* GameInput)
{
	if (GetActiveGameState() == nullptr) {
		return;
	}

	GetActiveGameState()->ProcessInput(GameInput);
}


void SEGameStateMachine::CollectGabage()
{
	if (GetActiveGameState() == nullptr) {
		return;
	}

	GetActiveGameState()->CollectGarbage();

	if (GetActiveGameState()->IsPendingDestroy() && m_StackedGameState != nullptr) {
		// deleting the old game state
		delete m_ActiveGameState;
		// setting the active game state to the new one 
		SetActiveGameState(m_StackedGameState);
		// remove reference to the new game state from the stacked game state
		m_StackedGameState = nullptr;

		SELog("Switched state.");
	}
}

void SEGameStateMachine::SetActiveGameState(SEGameState* GameState)
{
	m_ActiveGameState = GameState;
	GetActiveGameState()->BeginPlay();
}

void SEGameStateMachine::SwapGameState(SEGameState* NextState)
{
	m_StackedGameState = NextState;
	GetActiveGameState()->destroy();
}
