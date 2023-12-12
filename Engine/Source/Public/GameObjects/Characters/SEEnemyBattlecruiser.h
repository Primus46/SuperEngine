#pragma once
#include "GameObjects/Characters/SEEnemy.h"
class SEEnemyBattlecruiser :
    public SEEnemy
{
public:
    SEEnemyBattlecruiser(SEString DefaultName, Window* AssignedWindow);

    virtual void BeginPlay();

    virtual void Update(float DeltaTime) override;

protected:
    void TryShoot();

protected:
    float m_ShootTimer;

    float m_FireRate;
};

