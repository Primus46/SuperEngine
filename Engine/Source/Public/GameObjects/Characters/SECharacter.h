#pragma once
#include "GameObjects/SEGameObject.h"

class SESpriteComponent;
class SEMovementComponent;

class SECharacter : public SEGameObject{
public:
	SECharacter(SEString DefaultName, Window* AssignedWindow);

	void BeginPlay() override;

	void Update(float DeltaTime) override;

	TSharedPtr<SESpriteComponent> GetSpriteComponent() const { return m_SpriteComponent; }

	TSharedPtr<SEMovementComponent> GetMovementComponent() const { return m_MovementComponent; }

private:
	TSharedPtr<SESpriteComponent> m_SpriteComponent;

	TSharedPtr<SEMovementComponent> m_MovementComponent;
};