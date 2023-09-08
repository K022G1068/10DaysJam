#include "Enemy.h"

void Enemy::Initialize(
    Model* model, Model* gaugeModel, Vector3& playerPosition, ViewProjection& viewProjection, const char* name) {
	assert(model);
	// textureHandle_ = textureHandle;
	
	name_ = name;
	
	worldTransform_.Initialize();
	worldTransform_.translation_ = playerPosition;
	worldTransform_.scale_ = {1.5f, 1.5f, 1.5f};
	model_ = model;

	//Gauge
	gauge_ = new Gauge();
	Vector3 gaugePos_(0.0f, 15.0f, 0.0f);
	gauge_->Initialize(gaugeModel, gaugePos_, viewProjection, radius_);
	gauge_->SetParent(&worldTransform_);

	//Collider
	Vector3 colliderPos(0, 5.0f, 0.0f);
	Collider::BaseInit(viewProjection, showCollider_, name_);
	Collider::SetCollider(colliderPos, radius_);
	Collider::SetColliderParent(&worldTransform_);

}
Enemy::~Enemy() { delete gauge_; }

void Enemy::Update() {
	Movement();
	gauge_->Update();

	//Collider
	Collider::OnUpdate();
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
	gauge_->Draw(viewProjection);
	model_->Draw(worldTransform_, viewProjection);
}

void Enemy::DrawPrimitive() { 
	gauge_->DrawBox();
	Collider::DrawCollider();
}
