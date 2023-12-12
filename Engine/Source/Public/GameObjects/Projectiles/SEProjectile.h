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

    virtual void OnBeginOverlap(SECollision* Col) override;

    virtual void DestroyOnOverlap();

    virtual void Update(float DeltaTime) override;

protected:
    TSharedPtr<SEMovementComponent> GetMovementComponent() const { return m_Movement; }

    TSharedPtr<SESpriteComponent> GetMainSprite() const { return m_Sprite; }

    TSharedPtr<SECollisionComponent> GetMainCollision() const { return m_Collision; }

    virtual void OnObjectHit(SEGameObject* GameObject, SECollision* Col);

protected:
    SEObjectTypes m_CollisionType;

    int m_Damage;

     // how long the projectile has been in the game
    float m_LifeTimer;

    // how long until the projectile destroys itself
    float m_Lifetime;

    // how fast the projectile reaches it's max speed
    float m_Acceleration;

    // the singular direction the projectile moves in
    SEVector2 m_MoveDirection;

private:
    TSharedPtr<SEMovementComponent> m_Movement;

    TSharedPtr<SESpriteComponent> m_Sprite;

    TSharedPtr<SECollisionComponent> m_Collision;
};

