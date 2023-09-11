#include "Enemy.h"
#include "Goal.h"
#include "Spot.h"

void Enemy::Initialize(
    Model* model, Vector3& enemyPosition, ViewProjection& viewProjection, const char* name) {
	assert(model);
	// textureHandle_ = textureHandle;
	
	name_ = name;
	
	worldTransform_.Initialize();
	worldTransform_.translation_ = enemyPosition;
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

	//Dash
	dash_ = new Dash();
	dash_->Initialize(rotationSpeed_);

	// Easing
	easing_.time = 0;
	easing_.startPos = {0, 0, 0};
	easing_.duration = 20.0f;
	easing_.change = 10;
	// Easing2
	easing2_.time = 0;
	easing2_.startPos = {0, 0, 0};
	easing2_.duration = 20.0f;
	easing2_.change = 10;
}
Enemy::~Enemy() { delete gauge_; }

void Enemy::InitializeGauge(Model* gaugeModel, Model* gaugeModelBox) {
	// Gauge
	gauge_ = new Gauge();
	Vector3 gaugePos_(0.0f, 15.0f, 0.0f);
	gauge_->Initialize(gaugeModel, gaugeModelBox, gaugePos_, viewProjection_, radius_);
	//gauge_->SetParent(&worldTransform_);

	//State initialize
	// Random
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	random_number = std::rand() % 101;
	
	if (random_number == 50)
	{
		std::srand(static_cast<unsigned>(std::time(nullptr)));
		random_number = std::rand() % 101;
	}
	else if (random_number > percentageDash_)
	{
		state_ = new EnemyStateApproachGoal();
		state_->GetDistance(this);
	}
	else
	{
		state_ = new EnemyStateApproachSpot();
		state_->GetDistance(this);
	}
}

void Enemy::Update() {
	Movement();

	// State update
	state_->Update(this);

	//Gauge
	gauge_->GetCameraRotation(viewProjection_->rotation_.y);
	gauge_->SetPosition(worldTransform_.translation_);
	gauge_->GetRotation(rotationSpeed_);
	gauge_->Update();

	worldTransform_.rotation_ += rotationSpeed_;
	
	ImGui::Text("Random Number %s: %d", name_, random_number);

	//Collider
	Collider::OnUpdate();

	FlyingToGoal();

	if (GetIsGoal())
	{
		ChangeState(new EnemyStateStop);
	}
	worldTransform_.translation_ += velocity_;
	
	worldTransform_.UpdateMatrix();
}

void Enemy::Movement() { 
	ImGui::Begin("Enemy movement");
	ImGui::DragFloat3("Position", &worldTransform_.translation_.x, 0.8f);
	ImGui::DragFloat3("RotationSpeed", &rotationSpeed_.x, 0.001f);
	ImGui::End();
}

void Enemy::OnCollision() { 
	TurnRED();
	Collider* collidedObject = GetCollidedCollider();
	Vector3 ObjectRotationSpeed = collidedObject->GetRotationSpeed();
	Vector3 posBeforeCollision = worldTransform_.translation_;
	if (rotationSpeed_.y < ObjectRotationSpeed.y) {
		isFlying_ = true;
		Vector3 posAfterCollision = worldTransform_.translation_;
		collisionPower_ = (ObjectRotationSpeed.y - rotationSpeed_.y) * 20.0f;
		toGoal_ = worldTransform_.translation_ - goalPos_;
		float lenght = Length(toGoal_);
		if (lenght >= collisionPower_) {
			toGoal_.x /= lenght;
			toGoal_.y /= lenght;
			toGoal_.z /= lenght;

			velocity_ = toGoal_;
		}
	}
}

void Enemy::SetColliderPosition() {
	colliderPos_.x = worldTransform_.translation_.x;
	colliderPos_.y = worldTransform_.translation_.y + radius_;
	colliderPos_.z = worldTransform_.translation_.z;
}

void Enemy::FlyingToGoal() {
	if (isFlying_) {
		// How far is the object going to fly
		float limit = collisionPower_ * 50.0f + 50.0f;

		ImGui::Text("Enemy Limit %f", limit);
		totalCollisionDash += velocity_ * dash_->EaseInQuad(easing2_) * -collisionPower_ * 5.0f;
		ImGui::Text("enemy Totaldash %f", Length(totalCollisionDash));
		worldTransform_.translation_ +=
		    velocity_ * dash_->EaseInQuad(easing2_) * -collisionPower_ * 5.0f;
		if (Length(totalCollisionDash) >= limit) {
			dash_->DisactivateDash(easing2_);
			totalCollisionDash = {0.0f, 0.0f, 0.0f};
			velocity_ = {0, 0, 0};
			isFlying_ = false;
		}
	}
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::ChangeState(BaseEnemyState* enemyState) {
	//Find the nearest enemy and spot
	enemyState->GetDistance(this);

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
	toGoal_ = e->GetWorldTransform().translation_ - goalPos_;
	Move(toGoal_, e);

	ImGui::Text("%f %f %f", velocity_);
}

void EnemyStateStop::Update(Enemy* e) { 
	Vector3 velocity = {0, 0, 0};
	e->SetVelocity(velocity);
}

void EnemyStateApproachEnemy::Update(Enemy* e) { e->Movement(); }

void EnemyStateApproachSpot::Update(Enemy* e) { 
	ImGui::Text("Nearest pos %f %f %f", nearestPos_.x, nearestPos_.y, nearestPos_.z);
	toSpot_ = e->GetWorldTransform().translation_ - nearestPos_;
	ImGui::Text("ToSpot %f %f %f", toSpot_.x, toSpot_.y, toSpot_.z);
	Move(toSpot_, e);
}

void BaseEnemyState::GetDistance(Enemy* e) {
	float length = 10000.0f;
	spotPos_ = e->GetSpot();
	// ImGui::Text("Nearest pos %f %f %f", nearestPos_);
	std::list<Vector3>::iterator itrA = spotPos_.begin();
	for (; itrA != spotPos_.end(); ++itrA) {
		Vector3 A = *itrA;
		Vector3 difference = e->GetWorldTransform().translation_ - A;
		float differenceLength = Length(difference);
		if (differenceLength < length) {
			length = Length(difference);
			nearestPos_ = A;
		}
	}
}

void BaseEnemyState::Move(Vector3 velocity, Enemy* e) {
	float lenght = Length(velocity);
	if (lenght >= 0.1f) {
		velocity.x /= lenght;
		velocity.y /= lenght;
		velocity.z /= lenght;

		velocity_ = {velocity.x * -0.5f, velocity.y * -0.5f, velocity.z * -0.5f};

		// velocity_ = TransformNormal(velocity_, e->GetWorldTransform().matWorld_);
		e->SetVelocity(velocity_);
	} else {
		e->ChangeState(new EnemyStateStop);
	}
}

void EnemyStateNothing::Update(Enemy* e) { e->Movement(); }
