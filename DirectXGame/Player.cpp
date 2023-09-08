#include "Player.h"
//#include "PlayerCamera.h"

void Player::Initialize(
    Model* model, Model* gaugeModel, Vector3& playerPosition, ViewProjection& viewProjection,
    const char* name) {
	assert(model);
	//textureHandle_ = textureHandle;
	name_ = name;
	BaseInit(viewProjection, showCollider_, name_);
	worldTransform_.Initialize();
	worldTransform_.translation_ = playerPosition;
	worldTransform_.scale_ = {1.4f, 1.4f, 1.4f};
	model_ = model;
	input_ = Input::GetInstance();
	mode_ = gaugeModel;
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

	//Dash
	dash_ = new Dash();
	dash_->Initialize(rotationSpeed_);
}

Player::~Player() {}

void Player::Update() {
	Move();
	gauge_->Update();
	gauge_->GetCameraRotation(viewProjection_->rotation_.y);
	Collider::OnUpdate();
	//worldTransform_.rotation_.y -= viewProjection_->rotation_.y;
	worldTransform_.rotation_.y -= 0.25f;
	
	worldTransform_.UpdateMatrix();
}


Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

void Player::OnCollision() { ImGui::Text("HOOOOTTTTTTT"); }

void Player::SetColliderPosition() {
	colliderPos_.x = worldTransform_.translation_.x;
	colliderPos_.y = worldTransform_.translation_.y + radius_;
	colliderPos_.z = worldTransform_.translation_.z;
}

void Player::Move() {
	
	Vector3 move = {0, 0, 0};
	
	const float kCharacterSpeed = 0.5f;

	if (Input::GetInstance()->GetJoystickState(0, joyState_)) {
		if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState_))
		{
			move = {
			    (float)joyState_.Gamepad.sThumbLX / SHRT_MAX, 0.1f,
			    (float)joyState_.Gamepad.sThumbLY / SHRT_MAX};

			if (joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_A && !prevjoyState_.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
				worldTransform_.translation_ += dash_->easeOutQuint({0.0f, 0.0f, 50.0f});
			}

			move = Normalize(move) * kCharacterSpeed;
			move.y = 0.0f;

			Matrix4x4 rotmat = MakeRotationMatrixY(viewProjection_->rotation_.y);
			move = TransformNormal(move, rotmat);
		}
		
	} else {
		ImGui::Text("No controller detected");
	}
	
	worldTransform_.translation_ += move;
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
	gauge_->Draw(viewProjection);
}

void Player::DrawPrimitive() { 
	gauge_->DrawBox();
	Collider::DrawCollider();
}
