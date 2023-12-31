#pragma once
#include "GameStates/SEGameState.h"

class SEMainMenuState :
    public SEGameState
{
public:
	SEMainMenuState(Window* AssignedWindow)
		: SEGameState(AssignedWindow) {}

protected:
	virtual void OnBeginPlay() override;

	virtual void OnProcessInput(SEInput* GameInput) override;

};

