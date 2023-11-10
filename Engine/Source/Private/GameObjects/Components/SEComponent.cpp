#include "CoreMinimal.h"
#include "GameObjects/Components/SEComponent.h"

void SEComponent::Destroy()
{
	OnDestroy();
}
