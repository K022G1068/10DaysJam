#include "CollisionManager.h"

CollisionManager::CollisionManager() {}

CollisionManager::~CollisionManager() {}

void CollisionManager::Initialize() {

}

void CollisionManager::CheckAllCollisions() {
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {
		Collider* A = *itrA;

		// Iterator B
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != colliders_.end(); ++itrB) {
			Collider* B = *itrB;

			if (A->GetAttribute() == kCollisionAttributeGoal ||
			    A->GetAttribute() == kCollisionAttributeSpot) {
				if (SphereCollisionCheck(A, B)) {
					A->SetCollidedCollider(B);
					A->OnCollision();
				}
			} else if (
			    B->GetAttribute() == kCollisionAttributeGoal ||
			    B->GetAttribute() == kCollisionAttributeSpot) {
				if (SphereCollisionCheck(A, B)) {
					B->SetCollidedCollider(A);
					B->OnCollision();
				}
			}

			if (A->GetAttribute() == kCollisionAttributeGoal) {
				if (SphereCollisionCheck(A, B)) {
					B->SetIsGoal(true);
					A->OnCollision();
				}
			} else if (B->GetAttribute() == kCollisionAttributeGoal) {
				if (SphereCollisionCheck(A, B)) {
					A->SetIsGoal(true);
					B->OnCollision();
				}
			}
			
			if (!A->GetIsGoal() && !B->GetIsGoal())
			{
				if (SphereCollisionCheck(A, B)) {
					A->SetCollidedCollider(B);
					B->SetCollidedCollider(A);
					A->OnCollision();
					B->OnCollision();
				}
			}
		}
	}
}

bool CollisionManager::SphereCollisionCheck(Collider* s1, Collider* s2) {
	Vector3 firstPos;
	Vector3 secondPos;
	if (strcmp(s1->GetName(), "Goal") == 0)
	{
		firstPos = s1->GetColliderWorldPosition();
	}
	else
	{
		firstPos = s1->GetWorldPosition();
	}

	if (strcmp(s2->GetName(), "Goal") == 0) {
		secondPos = s2->GetColliderWorldPosition();
	} else {
		secondPos = s2->GetWorldPosition();
	}
	Vector3 distanceVector = Subtract(firstPos, secondPos);
	float distanceSq = Dot(distanceVector, distanceVector);
	float sumRadius = s1->GetCollider().radius + s2->GetCollider().radius;
	return distanceSq <= (sumRadius * sumRadius);
}


void CollisionManager::ClearList() { colliders_.clear(); }

void CollisionManager::Register(Collider* collider) { colliders_.push_back(collider); }

CollisionManager* CollisionManager::GetInstance() {
	static CollisionManager instance;
	return &instance;
}
