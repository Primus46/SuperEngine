#pragma once
#include "GameObjects/Components/SEComponent.h"

class SEAnimStateMachine;

class SESpriteComponent : public SEComponent {
public:
	SESpriteComponent(SEGameObject* Owner);

	bool AddAnimation(SEString PathToFile, SEAnimParams AnimParams);

	bool AddSingleSprite(SEString PathToFile, SESpriteParams SpriteParams = SESpriteParams());

	void SetSpriteIndex(SEUint Index);

	void BeginPlay() override;

	void Update(float DeltaTime) override;

	void ClearSprites();

protected:
	void OnDestroy() override;

private:
	void FollowGameObject();

private:
	// animation state machine for the sprite component
	SEAnimStateMachine* m_ASM;
};