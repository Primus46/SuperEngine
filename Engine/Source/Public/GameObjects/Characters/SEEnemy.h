#pragma once
#include "GameObjects/Characters/SECharacter.h"

struct Mix_Chunk;

class SEEnemy :
	public SECharacter
{
public:
	SEEnemy(SEString DefaultName, Window* AssignedWindow);
	
	void Update(float DeltaTime) override;

	void BeginPlay() override;

	void DestroyWithEffects();

private:
	// sprite component for engine effects animation
	TSharedPtr<SESpriteComponent> m_EngineEffects;

	// direction the enemy will move in
	SEVector2 m_MovementDir;

	//the acceleration power of the enemies
	float m_EnemyAcceleration;

	Mix_Chunk* m_DestroySFX[2] = { nullptr };
};