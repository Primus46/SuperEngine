#include "CoreMinimal.h"
#include "GameObjects/Components/SEMovementComponent.h"

#include "GameObjects/SEGameObject.h"
#include "GameObjects/Components/SETransformComponent.h"

#define GRAVITY 9.81f

SEMovementComponent::SEMovementComponent(SEGameObject* Owner)
	: SEComponent(Owner)
{
	m_Mass = 1.0f;
	m_Drag = 0.0f;
	m_MaxVelocity = 100.0f;
}

void SEMovementComponent::Update(float DeltaTime)
{
	if (GetTransform() == nullptr) {
		return;
	}

	float DragForce = GRAVITY + m_Drag;
	DragForce *= m_Mass;

	if (m_Velocity.Length() > 0.01f) {
		AddForce(-m_Velocity, DragForce);
	}
	else {
		m_Velocity = 0.0f;
	}
	
	m_Velocity += m_Accelaration;

	if (m_Velocity.Length() > m_MaxVelocity) {
		m_Velocity = m_Velocity.Normal() * m_MaxVelocity;
	}

	GetTransform()->Position += m_Velocity * DeltaTime;

	m_Accelaration = SEVector2::Zero();
}

void SEMovementComponent::AddForce(SEVector2 Direction, float Force)
{
	SEVector2 Acceleration = Direction.Normal() * Force;

	Acceleration /= std::max(m_Mass, 0.01f);

	m_Accelaration += Acceleration;
}

TSharedPtr<SETransformComponent> SEMovementComponent::GetTransform()
{
	return GetOwner()->GetTransform();
}
