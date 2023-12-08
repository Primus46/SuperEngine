#pragma once
#include "GameObjects/Components/SEComponent.h"
#include "Math/SEVector2.h"

class SETransformComponent;

class SEMovementComponent : public SEComponent{
public:
	SEMovementComponent(SEGameObject* Owner);

	void Update(float DeltaTime) override;

	// add force to the movement to accelerate the object
	void AddForce(SEVector2 Direction, float Force);

	// returns the current velocity of the component
	SEVector2 GetVelocity() const {return m_Velocity; }

protected:
	TSharedPtr<SETransformComponent> GetTransform();

public:
	// constant value against the velocity
	float m_Mass;
	
	// maximun possible velocity
	float m_Drag;

	float m_MaxVelocity;

private:
	SEVector2 m_Velocity;

	SEVector2 m_Accelaration;
};