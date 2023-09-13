#include "Player.h"
#include "Goal.h"
#include "GameManager.h"

void Player::Initialize(
    Model* model, Vector3& playerPosition, ViewProjection& viewProjection,
    const char* name) {
	assert(model);
	//textureHandle_ = textureHandle;
	name_ = name;
	BaseInit(viewProjection, showCollider_, name_);
	worldTransform_.Initialize();
	worldTransform_.translation_ = playerPosition;
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	model_ = model;
	input_ = Input::GetInstance();

	//Collider
	Vector3 colliderPos(0, 5.0f, 0.0f);
	Collider::BaseInit(viewProjection, showCollider_, name_);
	Collider::SetCollider(colliderPos, radius_);
	Collider::SetColliderParent(&worldTransform_);

	//Dash
	dash_ = new Dash();
	dash_->Initialize(rotationSpeed_);

	//Easing
	easing_.time = 0;
	easing_.startPos = {0,0,0};
	easing_.duration = 20.0f;
	easing_.change = 10;
	//Easing2
	easing2_.time = 0;
	easing2_.startPos = {0, 0, 0};
	easing2_.duration = 20.0f;
	easing2_.change = 10;

	SetRotationSpeed({0.0f, 0.06f, 0.0f});
	//Attribute
	SetAttribute(kCollisionAttributePlayer);
	SetMaskAttribute(kCollisionAttributeEnemy);
}

void Player::InitializeGauge(Model* gaugeModel, Model* gaugeModelBox) {
	// Gauge
	gauge_ = new Gauge();
	Vector3 gaugePos_(0.0f, 100.0f, 0.0f);
	gauge_->Initialize(gaugeModel, gaugeModelBox,gaugePos_, viewProjection_, gaugeRadius_);
	
}

Player::~Player() {}

void Player::Update() {

	worldTransform_.rotation_ += rotationSpeed_;
	//ImGui::Text(
	//    "collider world pos %s: %f %f %f", name_, Collider::GetColliderWorldPosition().x,
	//    Collider::GetColliderWorldPosition().y, Collider::GetColliderWorldPosition().z);
	//ImGui::Text("Player isGoal %d", GetIsGoal());
	//ImGui::Text("Goalie size %d", goal_->GetGoalieList().size());
	//ImGui::Text("Goal number %d", gameManager_->GetGoalNumber());

	if (!GetIsGoal())
	{
		rotationSpeed_.y -= 0.00035f;
		worldTransform_.rotation_ += rotationSpeed_;
		worldTransform_.translation_ += velocity_;

		//is Stoping
		if (isStoping_)
		{
			velocity_ = {0, 0, 0};
		}

		StopMovement();

		if (stage_->GetMode(worldTransform_.translation_) == onGrand) {
			worldTransform_.translation_.y =
			    stage_->GetGrandPosY(worldTransform_.translation_) - 30;
			acceleration_ = {.0f, .0f, .0f};
			if (!isStoping_)
			{
				Move();
			}
			
		}
		if (stage_->GetMode(worldTransform_.translation_) == underGrand) {
			acceleration_.y += stage_->grav_;
			worldTransform_.translation_.y -= acceleration_.y;
		}
		worldTransform_.UpdateMatrix();
		worldTransform_.translation_ += spotVelocity_;
		// プレイヤーの回転速度を徐々に遅くする
		
		kCharacterSpeed = (((rotationSpeed_.y - MIN_ROTATION) / (MAX_ROTATION - MIN_ROTATION)) * (MAX_CHARACTER_SPEED - MIN_CHARACTER_SPEED)) + MIN_CHARACTER_SPEED;
		if (rotationSpeed_.y <= MIN_ROTATION) {
			kCharacterSpeed = MIN_CHARACTER_SPEED;
		}
		if (rotationSpeed_.y >= MAX_ROTATION) {
			kCharacterSpeed = MAX_CHARACTER_SPEED;
		}
		//ImGui::Text("Character speed %f", kCharacterSpeed);
		if (Length(spotVelocity_) >= 0) {
			countSpotFlyingTimer_++;
			if (countSpotFlyingTimer_ >= 60) {
				spotVelocity_ = {0, 0, 0};
				countSpotFlyingTimer_ = 0;
			}
		}
		if (stage_->GetMode(worldTransform_.translation_) == underGrand &&
		    worldTransform_.translation_.y <= -120)
		{
			worldTransform_.translation_ = stage_->Respown();
			isStoping_ = true;
		}
			

		// Gauge
		gauge_->GetCameraRotation(viewProjection_->rotation_.y);
		gauge_->SetPosition(worldTransform_.translation_);
		gauge_->GetRotation(rotationSpeed_);
		gauge_->Update();

		// Dash
		if (rotationSpeed_.y < 0.3f * MAX_ROTATION) {
			dash_->SetCanDash(false);
		} else {
			dash_->SetCanDash(true);
		}

		Collider::OnUpdate();
		currentGoalCount = (int)goal_->GetGoalieList().size();
		FlyingToGoal();
		// ImGui
		//ImGui::DragFloat3("Position", &worldTransform_.translation_.x, 0.8f);
		//ImGui::DragFloat3("Rotation", &rotationSpeed_.x, 0.001f);
	}
	else
	{
		rotationSpeed_.y -= 0.001f;
		velocity_ = {0, 0, 0};
		collisionVelocity_ = {0, 0, 0};
		worldTransform_.translation_ = Lerp(
		    worldTransform_.translation_,
		    {goalPos_.x, goalPos_.y, goalPos_.z + GOAL_DEEPEST - (currentGoalCount * 10.0f)},
		    0.01f);
		worldTransform_.rotation_.x = GetRandomRotationDegree();
		worldTransform_.rotation_.z = GetRandomRotationDegree();

		if (worldTransform_.rotation_.x >= 0.4f) {
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

float Player::GetRandomRotationDegree() {
	std::srand(static_cast<unsigned>(std::time(nullptr)) + 1000);
	return (std::rand() % 629) / 100.0f;
}

void Player::StopMovement() {
	if (isStoping_)
	{
		countStopTime++;
		if (countStopTime >= STOP_TIME) {
			countStopTime = 0;
			isStoping_ = false;
		}
	}
	
}

void Player::Reset() {
	SetIsGoal(false);
	worldTransform_.translation_ = restartPos_;
	rotationSpeed_.y = 0.06f; 
	rotationSpeed_.z = 0.0f; 
	rotationSpeed_.x = 0.0f; 
	worldTransform_.rotation_.x = 0.0f;
	worldTransform_.rotation_.z = 0.0f;
	isStoping_ = false;
	isFlying_ = false;
	velocity_ = {0, 0, 0};
	collisionVelocity_ = {0, 0, 0};
	totalCollisionDash = {0, 0, 0};
	dash_->DisactivateDash(easing_);
	dash_->DisactivateDash(easing_);
	collisionPower_ = 0.0f;
	totalCollisionDash = {0, 0, 0};
	toGoal_ = {0, 0, 0};
	currentGoalCount = 0;
	SetIsGoal(false);
	worldTransform_.UpdateMatrix();
	
}

Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::FlyingToGoal() { 
	if (isFlying_) {
		//How far is the object going to fly
		float limit = collisionPower_ * 50.0f + 50.0f;

		//ImGui::Text("Limit %f", limit);
		if (goal_->GetGoalieList().size() <= gameManager_->GetGoalNumber()) {

			totalCollisionDash +=
			    collisionVelocity_ * dash_->EaseInQuad(easing2_) * -collisionPower_ * 5.0f;
			//ImGui::Text("Totaldash %f", Length(totalCollisionDash));
			worldTransform_.translation_ +=
			    collisionVelocity_ * dash_->EaseInQuad(easing2_) * -collisionPower_ * 5.0f;
			if (Length(totalCollisionDash) >= limit) {
				dash_->DisactivateDash(easing2_);
				totalCollisionDash = {0.0f, 0.0f, 0.0f};
				collisionVelocity_ = {0, 0, 0};
				isFlying_ = false;
			}
		} else
		{
			totalCollisionDash +=
			    collisionVelocity_ * dash_->EaseInQuad(easing2_) * collisionPower_ * 3.0f;
			//ImGui::Text("Totaldash %f", Length(totalCollisionDash));
			worldTransform_.translation_ +=
			    collisionVelocity_ * dash_->EaseInQuad(easing2_) * collisionPower_ * 3.0f;
			if (Length(totalCollisionDash) >= limit) {
				dash_->DisactivateDash(easing2_);
				totalCollisionDash = {0.0f, 0.0f, 0.0f};
				collisionVelocity_ = {0, 0, 0};
				isFlying_ = false;
			}
		}
	}
}

void Player::SetPositionLerp(Vector3 pos) { 
	
	worldTransform_.translation_ = Lerp(worldTransform_.translation_, pos, 0.2f); 
}

void Player::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

void Player::OnCollision() { 
	Collider* collidedObject = GetCollidedCollider();
	Vector3 ObjectRotationSpeed = collidedObject->GetRotationSpeed();
	
	if (strcmp(collidedObject->GetName(), "Goal") != 0 &&
	    strcmp(collidedObject->GetName(), "Spot") != 0)
	{
		dash_->DisactivateDash(easing_);
		velocity_ = {0, 0, 0};
		isStoping_ = true;
	}
	
	if (rotationSpeed_.y <= ObjectRotationSpeed.y)
	{
		isFlying_ = true;
		collisionPower_ = (ObjectRotationSpeed.y - rotationSpeed_.y) * 20.0f;
		toGoal_ = worldTransform_.translation_ - goalPos_;
		float lenght = Length(toGoal_);
		if (lenght >= collisionPower_) {
			toGoal_.x /= lenght;
			toGoal_.y /= lenght;
			toGoal_.z /= lenght;

			collisionVelocity_ = toGoal_;
			
		}
	}
	else
	{
		
	}
}

void Player::SetColliderPosition() {
	colliderPos_.x = worldTransform_.translation_.x;
	colliderPos_.y = worldTransform_.translation_.y + radius_;
	colliderPos_.z = worldTransform_.translation_.z;
}

void Player::Move() {

	if (Input::GetInstance()->GetJoystickState(0, joyState_)) {
		if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState_))
		{
			Vector3 move = {0, 0, 0};
			Vector3 totalDash = {0, 0, 0};
			
			
			if (easing_.time <= easing_.duration) {
				easing_.time += 0.01f;
			}

			move = {
			    (float)joyState_.Gamepad.sThumbLX / SHRT_MAX, 0.1f,
			    (float)joyState_.Gamepad.sThumbLY / SHRT_MAX
			};
			
			move = Normalize(move) * kCharacterSpeed;
			move.y = 0.0f;

			Matrix4x4 rotmat = MakeRotationMatrixY(viewProjection_->rotation_.y);
			move = TransformNormal(move, rotmat);

			if ((joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) && !(prevjoyState_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) && dash_->GetCanDash()) {
				//ImGui::Text("DASSSHHHH" );
				dash_->ActivateDash();
				float reduceAmount = 0.3f * MAX_ROTATION;
				rotationSpeed_.y -= reduceAmount;
			} 
			
			if (dash_->GetDash() == true)
			{
				move *= dash_->EaseInQuad(easing_) * 0.8f;
				totalDash += dash_->EaseInQuad(easing_) * 0.8f;
				if (Length(totalDash) >= 25.0f)
				{
					dash_->DisactivateDash(easing_);
				}
				move.y = 0.0f;
			} else {
				dash_->DisactivateDash(easing_);
			}

			


			//ImGui::Text("TotalDash", Length(totalDash));
			velocity_ = move;
			
		}
		
	} else {
		//ImGui::Text("No controller detected");
	}
	
	worldTransform_.translation_ += stage_->Sliding(worldTransform_.translation_);
	
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
	if (!GetIsGoal())
	{
		gauge_->Draw(viewProjection);
	}
}

void Player::DrawPrimitive() { 
	//gauge_->DrawBox();
	Collider::DrawCollider();
}
