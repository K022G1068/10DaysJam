#pragma once
#include "Collider.h"
#include <list>
class CollisionManager final{
protected:
	std::list<Collider*> colliders_;
	CollisionManager();
	~CollisionManager();

public:
	void Initialize();
	void CheckAllCollisions();
	bool SphereCollisionCheck(Collider* s1, Collider* s2);
	void ClearList();
	void Register(Collider* collider);

	CollisionManager& operator=(const CollisionManager& obj) = delete;
	CollisionManager(const CollisionManager& obj) = delete;
	static CollisionManager* GetInstance();
};
