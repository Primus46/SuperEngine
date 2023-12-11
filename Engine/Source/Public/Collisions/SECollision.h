#pragma once
#include "CoreMinimal.h"
#include "Collisions/SEBounds.h"

class SEGameObject;

enum SEObjectTypes : SEUint8 {
	OT_ALL = 0,
	OT_PLAYER,
	OT_ENEMY,
	OT_COLLECTABLE,
	OT_PROJECTILE
};

class SECollision {
public:
	SECollision(SEGameObject* Owner) : m_Owner(Owner), Debug(false), Type(OT_ALL){}
	// return the gameobject owner of this collisions
	SEGameObject* GetOwner() const { return m_Owner; }


public:
	// should this be dubugged (in case of window drawn to the screen)
	bool Debug;

	// the type of objects this collision is for
	SEObjectTypes Type;

	// the position and size of the collision
	// can also be used to determine overlap
	SEBoxBounds Bounds;

private:
	// the owner game object for the collision
	SEGameObject* m_Owner;
	
};