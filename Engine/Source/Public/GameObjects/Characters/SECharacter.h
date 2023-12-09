#pragma once
#include "GameObjects/SEGameObject.h"

class SESpriteComponent;
class SEMovementComponent;
class SECollisionComponent;

class SECharacter : public SEGameObject{
public:
	SECharacter(SEString DefaultName, Window* AssignedWindow);
	
	void BeginPlay() override;

	// get the main sprite component of the character
	TSharedPtr<SESpriteComponent> GetSpriteComponent() const { return m_SpriteComponent; }

	// get the movement component for the character
	TSharedPtr<SEMovementComponent> GetMovementComponent() const { return m_MovementComponent; }

	// get the collision component for the character
	TSharedPtr<SECollisionComponent> GetCollisionComponent() const { return m_CollisionComponent; }

	// get the of the character unscaled
	SEVector2 GetCharacterSize() const { return m_CharacterSize; }

	// get teh size of the character scaled
	SEVector2 GetScaledCharacterSize() const;

protected:
	// size of the character
	SEVector2 m_CharacterSize;

private:
	// the main sprite component for the character
	TSharedPtr<SESpriteComponent> m_SpriteComponent;

	// the movement component for the character
	TSharedPtr<SEMovementComponent> m_MovementComponent;

	// the main collision component for the game objects
	TSharedPtr<SECollisionComponent> m_CollisionComponent;
};