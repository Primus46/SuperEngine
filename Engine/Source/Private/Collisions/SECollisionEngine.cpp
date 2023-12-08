#include "CoreMinimal.h"
#include "Collisions/SECollisionEngine.h"
#include "Collisions/SECollision.h"

SECollisionEngine::~SECollisionEngine()
{
	// loop through all collisions and delete them 
	for (auto Col : m_CollisionStack) {
		delete Col;
	}

	// resize the array to 0
	m_CollisionStack.clear();
}

SECollision* SECollisionEngine::AddCollision(SEGameObject* Owner)
{
	// create the collision object
	SECollision* NewCol = new SECollision(Owner);

	// test id it was created
	if (NewCol != nullptr) {
		// if it was then add it to the stack
		m_CollisionStack.push_back(NewCol);
	}

	// return the collision in case the thing that created wants to use or store it
	return NewCol;
}

void SECollisionEngine::RemoveCollision(SECollision* Col)
{
	// loo through the WHOLE collision stack and see id the Collision exists
	// this returns the end() iterator if it didn't find the element (Col)
	auto it = std::find(m_CollisionStack.begin(), m_CollisionStack.end(), Col);
	
	// if we didn't find the element end the function
	if (it == m_CollisionStack.end()) {
		return;
	}
	
	// remove the collicion from memory
	delete* it;

	// remove the element from the array and resize the array
	m_CollisionStack.erase(it);
}
