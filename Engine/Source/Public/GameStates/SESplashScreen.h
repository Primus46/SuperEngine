#pragma once
#include "GameStates/SEGameState.h"

class SESplashScreen :
    public SEGameState
{
public:
	SESplashScreen(Window* AssignedWindow)
		: SEGameState(AssignedWindow) {}

protected:
	virtual void OnBeginPlay() override;

	virtual void OnProcessInput(SEInput* GameInput) override;
};

