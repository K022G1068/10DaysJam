#include "Enemy.h"

void Enemy::Initialize(
    Model* model, Vector3& playerPosition, ViewProjection& viewProjection, const char* name) {
	assert(model);
	// textureHandle_ = textureHandle;
	name_ = name;
	BaseInit(viewProjection, showCollider_, name_);
	worldTransform_.Initialize();
	worldTransform_.translation_ = playerPosition;
	model_ = model;
}
Enemy::~Enemy() {}

void Enemy::Update() {
	OnUpdate();
	Movement();
	SetColliderPosition();
	SetCollider(colliderPos_, radius_);
	worldTransform_.UpdateMatrix();
}

void Enemy::Movement() {}

void Enemy::OnCollision() { TurnRED(); }

void Enemy::SetColliderPosition() {
	colliderPos_.x = worldTransform_.translation_.x;
	colliderPos_.y = worldTransform_.translation_.y + radius_;
	colliderPos_.z = worldTransform_.translation_.z;
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
	//DrawCollider();
}
