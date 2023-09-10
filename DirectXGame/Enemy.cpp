#include "Enemy.h"
#include "Goal.h"
#include "Spot.h"

void Enemy::Initialize(
    Model* model, Vector3& playerPosition, ViewProjection& viewProjection, const char* name) {
	assert(model);
	// textureHandle_ = textureHandle;
	
	name_ = name;
	
	worldTransform_.Initialize();
	worldTransform_.translation_ = playerPosition;
	worldTransform_.scale_ = {1.5f, 1.5f, 1.5f};
	model_ = model;

	//Collider
	Vector3 colliderPos(0, 5.0f, 0.0f);
	Collider::BaseInit(viewProjection, showCollider_, name_);
	Collider::SetCollider(colliderPos, radius_);
	Collider::SetColliderParent(&worldTransform_);

	//Attribute
	SetAttribute(kCollisionAttributeEnemy);
	SetMaskAttribute(kCollisionAttributePlayer);

	//State
	state_ = new EnemyStateApproachGoal();

}
Enemy::~Enemy() { delete gauge_; }

void Enemy::InitializeGauge(Model* gaugeModel, Model* gaugeModelBox) {
	// Gauge
	gauge_ = new Gauge();
	Vector3 gaugePos_(0.0f, 15.0f, 0.0f);
	gauge_->Initialize(gaugeModel, gaugeModelBox, gaugePos_, viewProjection_, radius_);
	//gauge_->SetParent(&worldTransform_);
}

void Enemy::Update() {
	Movement();
	//Gauge
	gauge_->GetCameraRotation(viewProjection_->rotation_.y);
	gauge_->SetPosition(worldTransform_.translation_);
	gauge_->Update();
	//worldTransform_.rotation_.y -= 0.3f;

	//State update
	state_->Update(this);

	//Collider
	Collider::OnUpdate();

	worldTransform_.translation_ += velocity_;

	worldTransform_.UpdateMatrix();
}

void Enemy::Movement() { 
	ImGui::Begin("Enemy movement");
	ImGui::DragFloat3("Position", &worldTransform_.translation_.x, 0.8f);
	ImGui::End();
}

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

void Enemy::ChangeState(BaseEnemyState* enemyState) { 
	state_ = enemyState;
}

void Enemy::ApproachGoal() {
	
}

void Enemy::Stop() {}

void Enemy::ApproachSpot() {}

void Enemy::ApproachEnemy() {}

void Enemy::Draw(ViewProjection& viewProjection) {
	gauge_->Draw(viewProjection);
	model_->Draw(worldTransform_, viewProjection);
}

void Enemy::DrawPrimitive() { 
	//gauge_->DrawBox();
	Collider::DrawCollider();
}

void EnemyStateApproachGoal::Update(Enemy* e) {
	goalPos_ = e->GetGoal();
	toGoal_ = e->GetWorldPosition() - goalPos_;
	float lenght = Length(toGoal_);
	if (lenght >= 0.1f) {
		toGoal_.x /= lenght;
		toGoal_.y /= lenght;
		toGoal_.z /= lenght;

		velocity_ = {toGoal_.x * -0.5f, toGoal_.y * -0.5f, toGoal_.z * -0.5f};

		velocity_ = TransformNormal(velocity_, e->GetWorldTransform().matWorld_);
		e->SetVelocity(velocity_);
	}
	else
	{
		e->ChangeState(new EnemyStateStop);
	}

	ImGui::Text("%f %f %f", velocity_);
}

void EnemyStateStop::Update(Enemy* e) { 
	Vector3 velocity = {0, 0, 0};
	e->SetVelocity(velocity);
}

void EnemyStateApproachEnemy::Update(Enemy* e) { e->Movement(); }

void EnemyStateApproachSpot::Update(Enemy* e) { e->Movement(); }

void BaseEnemyState::GetDistance() { }
