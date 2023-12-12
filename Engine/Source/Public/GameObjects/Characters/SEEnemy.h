#pragma once
#include "GameObjects/Characters/SECharacter.h"

struct Mix_Chunk;

class SEEnemy :
	public SECharacter
{
public:
	SEEnemy(SEString DefaultName, Window* AssignedWindow);
	
	virtual void Update(float DeltaTime) override;

	virtual void BeginPlay() override;

	void DestroyWithEffects();

	virtual void OnDeath();

	int GetValue() const { return m_Value; }

	virtual void OnTakeDamage() override;



protected:
	// sprite component for engine effects animation
	TSharedPtr<SESpriteComponent> m_EngineEffects;
	
	// sprite component for weapon fire effects animation
	TSharedPtr<SESpriteComponent> m_WeaponsFireEffects;

	// direction the enemy will move in
	SEVector2 m_MovementDir;

	//the acceleration power of the enemies
	float m_EnemyAcceleration;

	Mix_Chunk* m_DestroySFX[2] = { nullptr };

	Mix_Chunk* m_Hurt;

	int m_Value;
};