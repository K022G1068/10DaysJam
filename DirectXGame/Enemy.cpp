#include "Enemy.h"
#include "Goal.h"
#include "Spot.h"
#include "Player.h"

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
	
	if (random_number == 50)
	{
		SetRandomNumber(1000);
	}
	else if (random_number > percentageDash_)
	{
		state_ = new EnemyStateStop();
		state_->SetTimer();
		state_->GetSpotDistance(this);
		state_->GetEnemyDistance(this);
	}
	else
	{
		state_ = new EnemyStateStop();
		state_->SetTimer();
		state_->GetSpotDistance(this);
	}
}

void Enemy::Update() {
	//Reduce rotation;
	rotationSpeed_.y -= 0.0001f;

	// State update
	
	state_->Update(this);
	//Gauge
	gauge_->GetCameraRotation(viewProjection_->rotation_.y);
	gauge_->SetPosition(worldTransform_.translation_);
	gauge_->GetRotation(rotationSpeed_);
	gauge_->Update();

	worldTransform_.rotation_ += rotationSpeed_;
	
	//ImGui::Text("Random Number %s: %d", name_, random_number);
	//ImGui::Text("EnemyCount %s: %d", name_, enemies_.size());
	

	ImGui::Text("GoalPos %s: %f %f %f", name_, goalPos_.x, goalPos_.y, goalPos_.z);
	ImGui::Text("Stop Time %s: %d", name_, state_->GetTimer());
	ImGui::Text("Count Time %s: %d", name_, state_->GetCountTimer());
	ImGui::Text("isGoal %s: %d", name_, GetIsGoal());

	

	//Collider
	if (!GetIsGoal())
	{
		Collider::OnUpdate();

		FlyingToGoal();

		if (GetIsGoal()) {
			ChangeState(new EnemyStateStop);
		}
		worldTransform_.translation_ += velocity_;
		worldTransform_.translation_ += spotVelocity_;

		if (Length(spotVelocity_) >= 0) {
			countSpotFlyingTimer_++;
			if (countSpotFlyingTimer_ >= 60) {
				spotVelocity_ = {0, 0, 0};
				countSpotFlyingTimer_ = 0;
			}
		}

		worldTransform_.UpdateMatrix();
	}
	else
	{
		velocity_ = {0,0,0};
		collisionVelocity_ = {0, 0, 0};
	}
	
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
	if (rotationSpeed_.y < ObjectRotationSpeed.y) {
		collisionVelocity_ = {0, 0, 0};
		collisionPower_ = (ObjectRotationSpeed.y - rotationSpeed_.y) * 20.0f;
		toGoal_ = worldTransform_.translation_ - goalPos_;
		float lenght = Length(toGoal_);
		toGoal_.x /= lenght;
		toGoal_.y /= lenght;
		toGoal_.z /= lenght;

		collisionVelocity_ = toGoal_;
		isFlying_ = true;
	
	}
}

void Enemy::SetColliderPosition() {
	colliderPos_.x = worldTransform_.translation_.x;
	colliderPos_.y = worldTransform_.translation_.y + radius_;
	colliderPos_.z = worldTransform_.translation_.z;
}

void Enemy::GetRandomRotation(int number) {
	std::srand(static_cast<unsigned>(std::time(nullptr)) + number);
	rotationSpeed_.y = (std::rand() % 11 + 10) /100.0f;
}

void Enemy::FlyingToGoal() {
	if (isFlying_) {
		// How far is the object going to fly
		float limit = collisionPower_ * 50.0f + 50.0f;

		ImGui::Text("Enemy Limit %f", limit);
		totalCollisionDash += collisionVelocity_ * dash_->EaseInQuad(easing2_) * -collisionPower_ * 5.0f;
		ImGui::Text("enemy Totaldash %f", Length(totalCollisionDash));
		worldTransform_.translation_ += collisionVelocity_ * dash_->EaseInQuad(easing2_) * -collisionPower_ * 5.0f;
		if (Length(totalCollisionDash) >= limit) {
			dash_->DisactivateDash(easing2_);
			totalCollisionDash = {0.0f, 0.0f, 0.0f};
			collisionVelocity_ = {0, 0, 0};

			//Stop the object
			//state_->SetTimer();
			this->ChangeState(new EnemyStateStop);
			isFlying_ = false;
		}
	}
}

void BaseEnemyState::SetTimer() {
	std::srand(static_cast<unsigned>(std::time(nullptr)) + 1000);
	stopTime_ = std::rand() % 121 + 60;
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::SetRandomNumber(int number) { 
	std::srand(static_cast<unsigned>(std::time(nullptr)) + number);
	random_number = std::rand() % 101;
}

void Enemy::ChangeState(BaseEnemyState* enemyState) {
	//Find the nearest enemy and spot
	enemyState->GetSpotDistance(this);
	enemyState->GetEnemyDistance(this);
	enemyState->SetTimer();
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
	ImGui::Text("Stop state");
	if (!e->GetIsGoal())
	{
		Vector3 velocity = {0, 0, 0};
		e->SetVelocity(velocity);
		stopTime_--;
		if (stopTime_ <= 0) {
			stopTime_ = 0;
			countTime_ = 0;
			e->SetRandomNumber(1000);
			if (e->GetRandomNumber() > e->GetPercetageDash()) {
				GetSpotDistance(e);
				GetEnemyDistance(e);
				e->ChangeState(new EnemyStateApproachEnemy);
			} else {
				GetSpotDistance(e);
				GetEnemyDistance(e);
				e->ChangeState(new EnemyStateApproachSpot);
			}
		}
	}
	
}

void EnemyStateApproachEnemy::Update(Enemy* e) {
	ImGui::Text( "%s Position: %f %f %f", e->GetName(), e->GetWorldTransform().translation_.x, e->GetWorldTransform().translation_.y, e->GetWorldTransform().translation_.z);
	ImGui::Text("%s NearestEnemy Position: %f %f %f",e->GetName(), nearestEnemyPos_.x, nearestEnemyPos_.y, nearestEnemyPos_.z);
	ImGui::Text("%s NearestEnemy name: %s",e->GetName(), nearestEnemyName_);
	toEnemy_ = e->GetWorldTransform().translation_ - nearestEnemyPos_;
	ImGui::Text("%s ToEnemy: %f %f %f",e->GetName(), toEnemy_.x, toEnemy_.y, toEnemy_.z);
	Move(toEnemy_, e);

	//If there is no collision
	if (Length(toEnemy_) <= 0.1f)
	{
		e->ChangeState(new EnemyStateStop);
	}
}

void EnemyStateApproachSpot::Update(Enemy* e) { 
	toSpot_ = e->GetWorldTransform().translation_ - nearestSpotPos_;
	Move(toSpot_, e);
	ImGui::Text("Spot and %s  %f", e->GetName(), Length(toSpot_));
	//ImGui::Text("Stop time %s  %d", e->GetName(), stopTime_);
	if (Length(toSpot_) <= 0.5f)
	{
		stopTime_--;
		if (stopTime_ <= 0)
		{
			e->ChangeState(new EnemyStateApproachEnemy);
			stopTime_ = 0;
		}
	}
}

void BaseEnemyState::GetSpotDistance(Enemy* e) {
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
			nearestSpotPos_ = A;		
		}
	}
}

void BaseEnemyState::GetEnemyDistance(Enemy* e) {
	float length = 10000.0f;
	float rotationSpeed = e->GetRotationSpeed().y;
	objects_ = e->GetObjects();

	std::list<Collider *>::iterator itrA = objects_.begin();
	for (; itrA != objects_.end(); ++itrA) {
		Collider* A = *itrA;
		if (A->GetRotationSpeed().y < rotationSpeed && A->GetRotationSpeed().y != rotationSpeed)
		{
			objectLowRotation_.push_back(A);
		}
	}

	// ImGui::Text("Nearest pos %f %f %f", nearestPos_);
	std::list<Collider *>::iterator itrB = objectLowRotation_.begin();
	for (; itrB != objectLowRotation_.end(); ++itrB) {
		Collider* B = *itrB;
		Vector3 difference = e->GetWorldTransform().translation_ - B->GetWorldTransform().translation_;
		float differenceLength = Length(difference);
		if (differenceLength < length && differenceLength > 0.0f) {
			length = Length(difference);
			nearestEnemyPos_ = B->GetWorldTransform().translation_;
			nearestEnemyName_ = B->GetName();
		}
	}
	 objects_.clear();
	 objectLowRotation_.clear();
}

void BaseEnemyState::Move(Vector3 velocity, Enemy* e) {
	float lenght = Length(velocity);
	if (lenght >= 0.1f) {
		velocity.x /= lenght;
		velocity.y /= lenght;
		velocity.z /= lenght;

		velocity_ = {velocity.x * -0.5f, velocity.y * -0.5f, velocity.z * -0.5f};
		velocity_.y = 0.0f;
		// velocity_ = TransformNormal(velocity_, e->GetWorldTransform().matWorld_);
		e->SetVelocity(velocity_);
	} else {
		e->ChangeState(new EnemyStateStop);
	}
}

void EnemyStateNothing::Update(Enemy* e) { e->Movement(); }
