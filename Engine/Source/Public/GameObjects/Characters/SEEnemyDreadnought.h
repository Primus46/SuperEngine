#pragma once
#include "GameObjects/Characters/SEEnemy.h"
class SEEnemyDreadnought :
    public SEEnemy
{
public:
    SEEnemyDreadnought(SEString DefaultName, Window* AssignedWindow);

    virtual void BeginPlay();

    virtual void Update(float DeltaTime) override;

protected:
    void TryShoot();

protected:
    float m_ShootTimer;

    float m_FireRate;
};

