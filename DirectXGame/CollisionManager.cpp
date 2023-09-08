#include "CollisionManager.h"

CollisionManager::CollisionManager() {}

CollisionManager::~CollisionManager() {}

void CollisionManager::Initialize() {}

void CollisionManager::CheckAllCollisions() {
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {
		Collider* A = *itrA;

		// Iterator B
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != colliders_.end(); ++itrB) {
			Collider* B = *itrB;
			if (SphereCollisionCheck(A, B)) {
				A->OnCollision();
				B->OnCollision();
			}
		}
	}
}

bool CollisionManager::SphereCollisionCheck(Collider* s1, Collider* s2) {
	Vector3 distanceVector =
	    Subtract(s1->GetCollider().sphereCenter, s2->GetCollider().sphereCenter);
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
