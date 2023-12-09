#include "CoreMinimal.h"
#include "GameObjects/Components/SECollisionComponent.h"
#include "Game.h"
#include "Collisions/SECollisionEngine.h"
#include "GameObjects/SEGameObject.h"

SECollisionComponent::SECollisionComponent(SEGameObject* Owner) : SEComponent(Owner)
{
	m_Collision = Game::GetGameInstance()->GetCollisions()->AddCollision(Owner);
}

void SECollisionComponent::BeginPlay()
{
	FollowOwner();
}

void SECollisionComponent::Update(float DeltaTime)
{
	FollowOwner();
	
	// loop through all the collisions in the game
	for (auto Col : Game::GetGameInstance()->GetCollisions()->GetCollisions()) {
		// if the collision is our collision then skip
		if (Col == m_Collision) {
			continue;
		}

		// ckech id we have already overlapped with the collision
		auto it = std::find(m_OverlappedCollisions.begin(), m_OverlappedCollisions.end(), Col);
		
		// if the collision is in the overlapping collision array
		if (it != m_OverlappedCollisions.end()) {
			// and we are no longer overlapping
			if (!m_Collision->Bounds.IsOverLapping(Col->Bounds)) {
				m_OverlappedCollisions.erase(it);
				// run the gameobject end overlap
				GetOwner()->OnEndOverlap(Col);
			}
		}
		// if the collision was not in the overlapped collision array
		else {
			// are we overlapping the bounds
			if (m_Collision->Bounds.IsOverLapping(Col->Bounds)) {
				m_OverlappedCollisions.push_back(Col);
				// run the gameobject begin overlap
				GetOwner()->OnBeginOverlap(Col);
			}
		}
	}

}

void SECollisionComponent::FollowOwner()
{
	// set the position of the bounding box to the position of the gameobject owner and offset the value
	m_Collision->Bounds.x = GetOwner()->GetTransform()->Position.x + BoundsOffset.x;
	m_Collision->Bounds.y = GetOwner()->GetTransform()->Position.y + BoundsOffset.y;

}
