#include "CoreMinimal.h"
#include "GameObjects/Projectiles/SEProjectile.h"

#include "GameObjects/Components/SECollisionComponent.h"
#include "GameObjects/Components/SEMovementComponent.h"
#include "GameObjects/Components/SESpriteComponent.h"

#include "GameObjects/Characters/SECharacter.h"

SEProjectile::SEProjectile(SEString DefaultName, Window* AssignedWindow)
	:SEGameObject(DefaultName, AssignedWindow)
{
	m_Collision = AddComponent<SECollisionComponent>();
	m_Movement = AddComponent<SEMovementComponent>();
	m_Sprite = AddComponent<SESpriteComponent>();

	m_Collision->GetCollision()->Bounds.w = 25.0f;
	m_Collision->GetCollision()->Bounds.h = 25.0f;
	// m_Collision->GetCollision()->Debug = true;

	m_CollisionType = SEObjectTypes::OT_ALL;

	m_Damage = 1;

	m_LifeTimer = 0.0f;
	m_Lifetime = 3.0f;

	m_MoveDirection = SEVector2(0.0f, -1.0f);
	m_Acceleration = 100.0f;
	m_Movement->m_MaxVelocity = 700.0f;
}

void SEProjectile::OnBeginOverlap(SECollision* Col)
{
	if (Col->Type == m_CollisionType) {
		OnObjectHit(Col->GetOwner(), Col);
		DestroyOnOverlap();
	}
}

void SEProjectile::DestroyOnOverlap()
{
	Destroy();
}

void SEProjectile::Update(float DeltaTime)
{
	SEGameObject::Update(DeltaTime);

	if (m_LifeTimer >= m_Lifetime) {
		Destroy();
		return;
	}

	m_LifeTimer += DeltaTime;

	GetMovementComponent()->AddForce(m_MoveDirection, m_Acceleration);
}

void SEProjectile::OnObjectHit(SEGameObject* GameObject, SECollision* Col)
{
	if (SECharacter* CharRef = dynamic_cast<SECharacter*>(GameObject)) {
		CharRef->ApplyDamage(m_Damage);
	}

	DestroyOnOverlap();
}
