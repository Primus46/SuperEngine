#pragma once
#include "GameObjects/SEGameObject.h"


class SEMovementComponent;
class SESpriteComponent;
class SECollisionComponent;


class SEProjectile :
    public SEGameObject
{
public:
    SEProjectile(SEString DefaultName, Window* AssignedWindow);

protected:
    TSharedPtr<SEMovementComponent> GetMovementComponent() const { return m_Movement; }

    TSharedPtr<SESpriteComponent> GetMainSprite() const { return m_Sprite; }

    TSharedPtr<SECollisionComponent> GetMainCollision() const { return m_Collision; }

private:
    TSharedPtr<SEMovementComponent> m_Movement;

    TSharedPtr<SESpriteComponent> m_Sprite;

    TSharedPtr<SECollisionComponent> m_Collision;
};

