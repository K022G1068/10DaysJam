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
	//gauge_ = new Gauge();
	//Vector3 gaugePos_(0.0f, 15.0f, 0.0f);
	//gauge_->Initialize(gaugeModel, gaugePos_, viewProjection, radius_);
	//gauge_->SetParent(&worldTransform_);


	//Collider
	Vector3 colliderPos(0, 5.0f, 0.0f);
	Collider::BaseInit(viewProjection, showCollider_, name_);
	Collider::SetCollider(colliderPos, radius_);
	Collider::SetColliderParent(&worldTransform_);
}

Player::~Player() {}

void Player::Update() {
	Move();
	//gauge_->Update();
	Collider::OnUpdate();

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

void Player::OnCollision() { ImGui::Text("HIOTTTTTTT"); }

void Player::SetColliderPosition() {
	colliderPos_.x = worldTransform_.translation_.x;
	colliderPos_.y = worldTransform_.translation_.y + radius_;
	colliderPos_.z = worldTransform_.translation_.z;
}

void Player::Move() {
	
	Vector3 move = {0, 0, 0};
	
	const float kCharacterSpeed = 0.2f;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		move = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed};

		//move = move * viewProjection_->rotation_;
		// move = Normalize(move) * kCharacterSpeed;
	} else {
		ImGui::Text("No controller detected");
	}
	
	worldTransform_.translation_ += move;
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
	//gauge_->Draw(viewProjection);
}

void Player::DrawPrimitive() { 
	//gauge_->DrawBox();
	Collider::DrawCollider();
}
