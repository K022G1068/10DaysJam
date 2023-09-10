#pragma once
#include "Model.h"
#include "Collider.h"
class Spot : public Collider {
public:
	void Initialize(Model* model, Vector3& spotPosition, ViewProjection& viewProjection);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void DrawPrimitive();
	void IncreaseRotationSpeed(Collider* collider);
	void OnCollision() override;
	Vector3 GetWorldPosition() override;
	const WorldTransform& GetWorldTransform() { return worldTransform_; };
	~Spot();

private:
	WorldTransform worldTransform_;
	Model* modelSpot_ = nullptr;
	float radius_ = 15.0f;
	bool showCollider_ = true;
	const char* name_ = "Spot";
};
