#pragma once
#include "GameObjects/Characters/SECharacter.h"
class SEPlayer :
    public SECharacter
{
public:
    SEPlayer(SEString DefaultName, Window* AssignedWindow);

    void Update(float DeltaTime) override;

    void ProcessInput(SEInput* GameInput) override;

private:
    SEVector2 m_MovementDir;

    float m_PlayerSpeed;
};

