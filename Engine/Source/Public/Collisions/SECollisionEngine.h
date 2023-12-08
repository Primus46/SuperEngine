#pragma once

class SECollision;
class SEGameObject;

class SECollisionEngine {
public:
	SECollisionEngine() = default;
	~SECollisionEngine();

	// get all the collisions in the engine
	TArray<SECollision*> GetCollisions() const { return m_CollisionStack; }

	// add a collision to the engine
	// must pass in the game object owner
	SECollision* AddCollision(SEGameObject* Owner);

	// remove the collision from the engine
	void RemoveCollision(SECollision* Col);


private:
	// store all collision in the engine
	TArray<SECollision*> m_CollisionStack;
};