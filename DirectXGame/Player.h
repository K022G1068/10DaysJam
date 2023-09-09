#pragma once
#include "Base.h"
#include "Collider.h"
#include "Input.h"
#include "Model.h"
#include "Stage.h"
class Player : public Collider {
public:
	void Initialize(
	    Stage*stage,Model* model, Vector3& playerPosition, ViewProjection& viewProjection, const char* name);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void SetParent(const WorldTransform* parent);
	void Move();
	~Player();
	void OnCollision() override;
	void SetColliderPosition();
	Vector3 GetWorldPosition() override;

private:
	WorldTransform worldTransform_;
	Vector3 colliderPos_;
	Vector3 rotationSpeed_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	float radius_ = 1.0f;
	bool showCollider_ = false;
	const char* name_;
	Stage* stage_;
};
