#include "CoreMinimal.h"
#include "GameStates/SEGameStateMachine.h"

#include "GameStates/SEGameState.h"

/*
SEGameStateMachine::~SEGameStateMachine()
{
	delete m_ActiveGameState;
}

void SEGameStateMachine::BeginPlay()
{
	if (GetActiveGameState() == nullptr) {
		SELog("No active game state assigned to the the state machine");
		return;
	}

	GetActiveGameState()->BeginPlay(); // change code here
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

	GetActiveGameState()->CollectGabage();
}

void SEGameStateMachine::SetActiveGameState(SEGameState* GameState)
{
	if (GetActiveGameState() != nullptr) {
		delete m_ActiveGameState;
	}
	m_ActiveGameState = GameState;

	GetActiveGameState()->BeginPlay();

}

*/