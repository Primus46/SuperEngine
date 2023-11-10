#pragma once
#include "GameObjects/Components/SEComponent.h"
#include "Math/SEVector2.h"

class SETransformationComponent;

class SEMovementComponent : public SEComponent{
public:
	SEMovementComponent(SEGameObject* Owner);

	void Update(float DeltaTime) override;

	void AddForce(SEVector2 Direction, float Force);

protected:
	TSharedPtr<SETransformationComponent> GetTransform();

public:

	float m_Mass;

	float m_Drag;

	float m_MaxVelocity;

private:
	SEVector2 m_Velocity;

	SEVector2 m_Accelaration;
};