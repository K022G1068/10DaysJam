#include "Enemy.h"
#include "Goal.h"
#include "Spot.h"
#include "Player.h"
#include "GameManager.h"
void Enemy::Initialize(
    Model* model, Vector3& enemyPosition, ViewProjection& viewProjection, const char* name) {
	assert(model);
	// textureHandle_ = textureHandle;
	
	name_ = name;
	goalNumber_ = gameManager_->GetGoalNumber();
	worldTransform_.Initialize();
	worldTransform_.translation_ = enemyPosition;
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
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
	gauge_->Initialize(gaugeModel, gaugeModelBox, gaugePos_, viewProjection_, gaugeRadius_);
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
	}
	else
	{
		state_ = new EnemyStateStop();
		state_->SetTimer();
		state_->GetSpotDistance(this);
	}
}

void Enemy::Update() {
	
	//ImGui::Text("Random Number %s: %d", name_, random_number);
	ImGui::Text("isGoal %s: %d", name_, GetIsGoal());
	worldTransform_.rotation_ += rotationSpeed_;
	
	ImGui::Text(
	    "collider world pos %s: %f %f %f", name_, Collider::GetColliderWorldPosition().x,
	    Collider::GetColliderWorldPosition().y, Collider::GetColliderWorldPosition().z);
	/*ImGui::Text("GoalPos %s: %f %f %f", name_, goalPos_.x, goalPos_.y, goalPos_.z);
	ImGui::Text("Stop Time %s: %d", name_, state_->GetTimer());
	ImGui::Text("Count Time %s: %d", name_, state_->GetCountTimer());
	ImGui::Text("isGoal %s: %d", name_, GetIsGoal());
	ImGui::Text("SpotVelocity: %f %f %f", spotVelocity_.x, spotVelocity_.y, spotVelocity_.z);
	ImGui::Text("NearEnemy: %d", state_->GetNearEnemyBool());*/

	/*ImGui::Text(
	    "%s NearestEnemy Position: %f %f %f", e->GetName(), nearestEnemyPos_.x, nearestEnemyPos_.y,
	    nearestEnemyPos_.z);
	ImGui::Text(
	    "%s NearestSpot: %f %f %f", e->GetName(), state_.get nearestSpotPos_.x, nearestSpotPos_.y,
	    nearestSpotPos_.z);*/
	//ImGui::Text("Nearenemy bool %d",nearEnemy_);
	//ImGui::Text("Nearenemy name %s: %s", name_, nearestEnemyName_);

	ImGui::Text("%s can dash: %d", name_, dash_->GetCanDash());
	//Collider
	if (!GetIsGoal())
	{
		// Reduce rotation;
		rotationSpeed_.y -= 0.0001f;
		state_->SetDash(dash_);
		Collider::OnUpdate();
		state_->Update(this);
		// State update
		if (goal_->GetGoalieList().size() == goalNumber_ - 1) {
			ChangeState(new EnemyStateApproachGoal);
		}

		// Gauge
		gauge_->GetCameraRotation(viewProjection_->rotation_.y);
		gauge_->SetPosition(worldTransform_.translation_);
		gauge_->GetRotation(rotationSpeed_);
		gauge_->Update();

		// Dash
		//  Dash
		if (rotationSpeed_.y < 0.3f * MAX_ROTATION) {
			dash_->SetCanDash(false);
		} else {
			dash_->SetCanDash(true);
		}

		
	

		{
			if (rotationSpeed_.y - 0.06f == 0.0f) {
				a_ = 0.0f;
			} else {
				a_ = (rotationSpeed_.y - 0.06f) * 4.16f * 100.0f;
			}

			percentageDash_ = int(a_);
			percentageSpot_ = 100 - int(a_);
		}

		if (easing_.time <= easing_.duration) {
			easing_.time += 0.01f;
		}

		currentGoalCount = (int)goal_->GetGoalieList().size();
		FlyingToGoal();
		if (stage_->GetMode(worldTransform_.translation_) != underGrand) {
			worldTransform_.translation_.y =
			    stage_->GetGrandPosY(worldTransform_.translation_) - 30;
		}
		if (stage_->GetMode(worldTransform_.translation_) == underGrand) {
			acceleration_.y += stage_->grav_;
			worldTransform_.translation_.y -= acceleration_.y;
		}
		if (worldTransform_.translation_.y <= -60)
		{
			velocity_ = {0, 0, 0};
			spotVelocity_ = {0, 0, 0};
			collisionVelocity_ = {0, 0, 0};
			worldTransform_.translation_ = stage_->Respown();
		}
			

		if (GetIsGoal()) {
			ChangeState(new EnemyStateStop);
		}
		worldTransform_.translation_ += velocity_;
		worldTransform_.translation_ += spotVelocity_;
		worldTransform_.translation_ += dashVelocity_;

		if (Length(spotVelocity_) > 0) {
			countSpotFlyingTimer_++;
			if (countSpotFlyingTimer_ >= 60) {
				spotVelocity_ = {0, 0, 0};
				countSpotFlyingTimer_ = 0;
				ChangeState(new EnemyStateStop);
			}
		}
	
	}
	else
	{
		rotationSpeed_.y -= 0.001f;
		velocity_ = {0,0,0};
		collisionVelocity_ = {0, 0, 0};
		worldTransform_.translation_ = Lerp(
		    worldTransform_.translation_,
		    {goalPos_.x, goalPos_.y, goalPos_.z + GOAL_DEEPEST - (currentGoalCount * 10.0f)},
		    0.01f);
		worldTransform_.rotation_.x = GetRandomRotationDegree();
		worldTransform_.rotation_.z = GetRandomRotationDegree();

		if (worldTransform_.rotation_.x >= 0.4f)
		{
			worldTransform_.rotation_.x = 0.4f;
		}
		if (worldTransform_.rotation_.x <= -0.4f) {
			worldTransform_.rotation_.x = -0.4f;
		}
		if (worldTransform_.rotation_.z >= 0.4f) {
			worldTransform_.rotation_.z = 0.4f;
		}
		if (worldTransform_.rotation_.z <= -0.4f) {
			worldTransform_.rotation_.z = -0.4f;
		}
		if (rotationSpeed_.y <= 0) {
			rotationSpeed_.y = 0;
		}
	}
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
	if (rotationSpeed_.y < ObjectRotationSpeed.y) {
		if (strcmp(collidedObject->GetName(), "Spot") != 0)
		{
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
}

void Enemy::SetColliderPosition() {
	colliderPos_.x = worldTransform_.translation_.x;
	colliderPos_.y = worldTransform_.translation_.y + radius_;
	colliderPos_.z = worldTransform_.translation_.z;
}

void Enemy::SetRandomRotationSpeed(int number) {
	std::srand(static_cast<unsigned>(std::time(nullptr)) + number);
	rotationSpeed_.y = (std::rand() % 21 + 10) /100.0f;
}

float Enemy::GetRandomRotationDegree() {
	std::srand(static_cast<unsigned>(std::time(nullptr)) + 1000);
	return (std::rand() % 629) / 100.0f;
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

void Enemy::SetPositionLerp(Vector3 pos) {
	/*ImGui::Begin("SetposLerp");
	ImGui::Text(
	    "Pos %f %f %f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z);
	ImGui::Text("Destination %f %f %f", pos.x,pos.y, pos.z);*/
	worldTransform_.translation_ = Lerp(worldTransform_.translation_, pos, 0.5f);
}

void Enemy::DoDash(Vector3 direction) {
	if (dash_->GetDash()) {
		ImGui::Text("%s is dashing", name_);
		direction *= dash_->EaseInQuad(easing_) * -1.2f;
		totalDash += dash_->EaseInQuad(easing_) * -1.2f;
		direction.y = 0.0f;
		worldTransform_.translation_ += direction;
		if (Length(totalDash) >= 50.0f) {
			dash_->DisactivateDash(easing_);
			totalDash = {0, 0, 0};
			ChangeState(new EnemyStateStop);
		}
		
	} else {
		dash_->DisactivateDash(easing_);
		totalDash = {0, 0, 0};
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
	enemyState->SetTimer();
	state_ = enemyState;
}

void Enemy::ApproachGoal() {
	
}

void Enemy::Stop() {}

void Enemy::ApproachSpot() {}

void Enemy::ApproachEnemy() {}

void Enemy::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
	if (!GetIsGoal()) {
		gauge_->Draw(viewProjection);
	}
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
			e->SetRandomNumber(1000);
			if (e->GetRandomNumber() < e->GetPercetageDash()) {
				GetSpotDistance(e);
				GetEnemyDistance(e);
				if (dash_->GetCanDash()) {
					
					float reduceAmount = 0.3f * MAX_ROTATION;
					Vector3 rotationSpeed = e->GetRotationSpeed();
					rotationSpeed.y -= reduceAmount;
					e->SetRotationSpeed(rotationSpeed);
					e->ChangeState(new EnemyStateApproachEnemy);
					GetSpotDistance(e);
					GetEnemyDistance(e);
				}
			} else {
				GetSpotDistance(e);
				GetEnemyDistance(e);
				e->ChangeState(new EnemyStateApproachSpot);
			}
		}
	}
	
}

void EnemyStateApproachEnemy::Update(Enemy* e) {
	if (e->GetNearEnemyBool())
	{
		ImGui::Text("Approach enemy state");
		
		/*ImGui::Text(
		    "%s Position: %f %f %f", e->GetName(), e->GetWorldTransform().translation_.x,
		    e->GetWorldTransform().translation_.y, e->GetWorldTransform().translation_.z);
		ImGui::Text(
		    "%s NearestEnemy Position: %f %f %f", e->GetName(), e->GetNearestEnemyPosition().x,
		    e->GetNearestEnemyPosition().y, e->GetNearestEnemyPosition().z);
		ImGui::Text("%s NearestEnemy name: %s", e->GetName(), e->GetNearestEnemyName());*/
		toEnemy_ = e->GetWorldTransform().translation_ - e->GetNearestEnemyPosition();
		//ImGui::Text("%s ToEnemy: %f %f %f", e->GetName(), toEnemy_.x, toEnemy_.y, toEnemy_.z);
		//ImGui::Text("%s ToEnemyLength: %f", e->GetName(), Length(toEnemy_));
		if (dash_->GetDash())
		{
			dash_->ActivateDash();
			Vector3 toEnemyNormal = Normalize(toEnemy_);
			e->DoDash(toEnemyNormal);
		}
		else
		{
			Move(toEnemy_, e);
		}
	

		// If there is no collision
		if (Length(toEnemy_) <= 0.5f) {
			GetSpotDistance(e);
			GetEnemyDistance(e);
			e->ChangeState(new EnemyStateStop);
		}
	} else {
		GetSpotDistance(e);
		GetEnemyDistance(e);
		e->ChangeState(new EnemyStateApproachSpot);

	}
	
}

void EnemyStateApproachSpot::Update(Enemy* e) { 
	GetSpotDistance(e);
	ImGui::Text("%s To Spot state", e->GetName());
	
	toSpot_ = e->GetWorldTransform().translation_ - nearestSpotPos_;
	Move(toSpot_, e);
	
	ImGui::Text("toSpot length %s  %f", e->GetName(), Length(toSpot_));
	if (e->GetIsOnSpot())
	{
		stopTime_--;
		GetEnemyDistance(e);
		ImGui::Text("%s StopTime %d", e->GetName(), stopTime_);
		if (stopTime_ <= 0) {
			
			if (e->GetNearEnemyBool()) {
				GetSpotDistance(e);
				GetEnemyDistance(e);
				if (dash_->GetCanDash()) {
					float reduceAmount = 0.3f * MAX_ROTATION;
					Vector3 rotationSpeed = e->GetRotationSpeed();
					rotationSpeed.y -= reduceAmount;
					e->SetRotationSpeed(rotationSpeed);
					e->ChangeState(new EnemyStateApproachEnemy);
					GetSpotDistance(e);
					GetEnemyDistance(e);
				}
				e->ChangeState(new EnemyStateApproachEnemy);
				stopTime_ = 0;
			}
			else
			{
				SetTimer();
			}
			e->SetIsOnSpot(false);
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
		if (std::strcmp(A->GetName(), e->GetName()) != 0)
		{
			if (A->GetRotationSpeed().y < rotationSpeed) {
				objectLowRotation_.push_back(A);
			}
		}
		
	}

	if (objectLowRotation_.size() <= 0)
	{
		e->SetNearEnemyBool(false);
	}

	// ImGui::Text("Nearest pos %f %f %f", nearestPos_);
	std::list<Collider *>::iterator itrB = objectLowRotation_.begin();
	for (; itrB != objectLowRotation_.end(); ++itrB) {
		Collider* B = *itrB;
		Vector3 difference = e->GetWorldTransform().translation_ - B->GetWorldTransform().translation_;
		float differenceLength = Length(difference);
		if (differenceLength < length) {
			length = Length(difference);
			e->SetNearEnemyBool(true);
			e->SetNearestEnemyPosition(B->GetWorldTransform().translation_);
			e->SetNearestEnemyName(B->GetName());
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

void BaseEnemyState::DashMove(Vector3 velocity, Enemy* e) {
	float lenght = Length(velocity);
	Vector3 totalDash = {0, 0, 0};
	Vector3 move = {0, 0, 0};
	if (lenght >= 0.1f) {
		velocity.x /= lenght;
		velocity.y /= lenght;
		velocity.z /= lenght;

		// velocity_ = TransformNormal(velocity_, e->GetWorldTransform().matWorld_);
		
		if (dash_->GetDash() == true) {
			move *= dash_->EaseInQuad(easing_) * 5.0f;
			totalDash += dash_->EaseInQuad(easing_);
			e->SetDashVelocity(move);
			if (Length(totalDash) >= 30.0f) {
				e->SetDashVelocity({0,0,0});
				dash_->DisactivateDash(easing_);
			}
			move.y = 0.0f;
		} else {
			e->SetDashVelocity({0, 0, 0});
			dash_->DisactivateDash(easing_);
		}

	} else {
		e->ChangeState(new EnemyStateStop);
	}
}

void BaseEnemyState::EasingInitialize() {

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

void EnemyStateNothing::Update(Enemy* e) {
	GetEnemyDistance(e);
	GetSpotDistance(e);
	ImGui::Text(
	    "%s NearestEnemy Position: %f %f %f", e->GetName(), e->GetNearestEnemyPosition().x,
	    e->GetNearestEnemyPosition().y, e->GetNearestEnemyPosition().z);
	ImGui::Text(
	    "%s NearestSpot: %f %f %f", e->GetName(), nearestSpotPos_.x, nearestSpotPos_.y,
	    nearestSpotPos_.z);
	ImGui::Text("Nearenemy bool %d", e->GetNearEnemyBool());

}
