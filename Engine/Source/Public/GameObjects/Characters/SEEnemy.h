#pragma once
#include "GameObjects/Characters/SECharacter.h"

class SEEnemy :
	public SECharacter
{
public:
	SEEnemy(SEString DefaultName, Window* AssignedWindow);
	
	void Update(float DeltaTime) override;

private:
	// sprite component for engine effects animation
	TSharedPtr<SESpriteComponent> m_EngineEffects;

	// direction the enemy will move in
	SEVector2 m_MovementDir;

	//the acceleration power of the enemies
	float m_EnemyAcceleration;
};