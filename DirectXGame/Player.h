#pragma once
#include "Base.h"
#include "Input.h"
#include "Collider.h"
#include "Model.h"
class Player : public Collider
{
public:
	void Initialize(Model* model, Vector3& playerPosition, ViewProjection& viewProjection);
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
	float radius_ =1.0f;
};
