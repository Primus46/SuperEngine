#pragma once
#include "GameObjects/Components/SEComponent.h"
#include "Math/SEVector2.h"

class SETransformComponent : public SEComponent {
public:
	SETransformComponent(SEGameObject* Owner) 
		: Position(SEVector2(0.0f)), Scale(SEVector2(1.0f)), Rotation(0.0f), SEComponent(Owner) {}

	SEVector2 Position;
	SEVector2 Scale;
	float Rotation;

};
