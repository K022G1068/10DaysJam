#pragma once
#include "Collider.h"
#include "Model.h"
#include <list>

class Goal : public Collider
{
public:
	void Initialize(Model* model, Vector3& goalPosition, ViewProjection& viewProjection);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void DrawPrimitive();
	void OnCollision() override;
	void SetColliderPosition();
	Vector3 GetWorldPosition() override;
	const WorldTransform& GetWorldTransform() { return worldTransform_; };
	~Goal();

private:
	WorldTransform worldTransform_;
	int komaCount_ = 0;
	Model* modelGoal_ = nullptr;
	float radius_ = 15.0f;
	bool showCollider_ = true;
	const char* name_ = "Goal";

	//List to keep track of the enemy that has enter the goal
	Collider* object_;
	std::list<Collider*> goalieList_;
};
