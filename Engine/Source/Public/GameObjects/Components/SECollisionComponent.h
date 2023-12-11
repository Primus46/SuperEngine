#pragma once
#include "SEComponent.h"

#include "Collisions/SECollision.h"


class SECollisionComponent :
	public SEComponent 
{
public:
	SECollisionComponent(SEGameObject* Owner);

	virtual void BeginPlay() override;

	virtual void Update(float DeltaTime) override;

	// returns the collision attached to this component
	SECollision* GetCollision() const { return m_Collision; }

protected:
	virtual void OnDestroy() override;

private:
	// set the position of the bounds to the position of the gameobject
	void FollowOwner();

public:
	// the offset of the collision bounds
	// usefull if you need to offset the collision from relative position of the object
	SEBoxBounds BoundsOffset;
private:
	// Collision attached to this component
	SECollision* m_Collision;

	// store the collisions we are currently overlapped with
	TArray<SECollision*> m_OverlappedCollisions;
};