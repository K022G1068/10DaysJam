#pragma once
#define FULL_CIRCLE 6.28f
#define MAX_STAY_TIME 180
#include "Model.h"
#include "Collider.h"
#include <cstdlib>
#include <ctime>
class Spot : public Collider {
public:
	void Initialize(Model* model, Vector3& spotPosition, ViewProjection& viewProjection);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void DrawPrimitive();
	void IncreaseRotationSpeed(Collider* collider);
	void SetRandomDirection();
	void OnCollision() override;
	Vector3 GetWorldPosition() override;
	const WorldTransform& GetWorldTransform() { return worldTransform_; };
	const char* GetName() override { return name_; };
	~Spot();
	void SetVelocity(Vector3 velocity) override { velocity_ = velocity; };

private:
	WorldTransform worldTransform_;
	Model* modelSpot_ = nullptr;
	float radius_ = 15.0f;
	bool showCollider_ = true;
	float degree_ = 0.0f;
	const char* name_ = "Spot";
	int countTime_ = 0;
	Vector3 velocity_;
};
