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

	// get the lives left of the character
	int GetLives() const { return m_Lives; }

	// apply damafe to the lives of the character
	// will run OnDeath once when the character lives fall on or below 0
	void ApplyDamage(int Damage = 1);

	// runs if the character lives fall on or below o
	virtual void OnDeath();

protected:
	// size of the character
	SEVector2 m_CharacterSize;

	// Health
	int m_Lives;

private:
	// the main sprite component for the character
	TSharedPtr<SESpriteComponent> m_SpriteComponent;

	// the movement component for the character
	TSharedPtr<SEMovementComponent> m_MovementComponent;

	// the main collision component for the game objects
	TSharedPtr<SECollisionComponent> m_CollisionComponent;

	// checks to see if the character has died
	bool m_IsDead;
};