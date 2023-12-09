#pragma once
#include "GameObjects/Characters/SECharacter.h"
class SEPlayer :
    public SECharacter
{
public:
    SEPlayer(SEString DefaultName, Window* AssignedWindow);

    void BeginPlay() override;

    void Update(float DeltaTime) override;

    void ProcessInput(SEInput* GameInput) override;

    void OnBeginOverlap(SECollision* Col) override;

    void OnEndOverlap(SECollision* Col) override;

private:
    // limit the players movement on the x-axis to stop the player off the screen
    void LimitPlayerX();

private:
    // The direction that we move based on player input
    SEVector2 m_MovementDir;

    // players accelartion
    float m_PlayerAcceleration;

    // store the Mainship sprite component
    TSharedPtr<SESpriteComponent> m_MainshipSprite;
};

