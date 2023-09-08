#pragma once
#include "Base.h"
#include "Input.h"
#include "Collider.h"
#include "Model.h"
#include "Gauge.h"

class Enemy : public Collider
{
public:
	void Initialize(
	    Model* model, Model* gaugeModel, Vector3& playerPosition, ViewProjection& viewProjection,
	    const char* name);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void DrawPrimitive();
	void Movement();
	~Enemy();
	void OnCollision() override;
	void SetColliderPosition();
	Vector3 GetWorldPosition() override;

private:
	WorldTransform worldTransform_;
	Vector3 colliderPos_;
	Vector3 rotationSpeed_;
	Model* model_ = nullptr;
	Gauge* gauge_ = nullptr;
	Model* gaugeModel_ = nullptr;
	uint32_t textureHandle_ = 0u;
	float radius_ = 11.0f;
	bool showCollider_ = true;
	const char* name_;
};
