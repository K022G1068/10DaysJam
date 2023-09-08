#include "Player.h"
#include "PlayerCamera.h"

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

Player::~Player() {}

void Player::Update() {
	gauge_->Update();
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
	
	/*if (input_->GetNumberOfJoysticks() > 0)
	{
		input_->GetJoystickState(0, joystick_.state_.directInput_);
		joystick_.state_.xInput_.dwPacketNumber = input_->GetWheel();
		const float kCharacterSpeed = 0.2f;
		Vector3 move = {
		    (float)joystick_.state_., 0.0f, (float)joystick_.state_.directInput_.lZ};
		move = Normalize(move) * kCharacterSpeed;

		worldTransform_.translation_ += move;
	}
	else
	{
		ImGui::Text("No controller detected");
	}
	*/
	Vector3 degree = {0, 0, 0};
	//float kCharacterSpeed = 0.3f;

	//if (input_->PushKey(DIK_A)) {
	//	degree.x -= kCharacterSpeed;
	//} else if (input_->PushKey(DIK_D)) {
	//	degree.x += kCharacterSpeed;
	//}

	//if (input_->PushKey(DIK_SPACE)) {
	//	// move.y += kCharacterSpeed;
	//} else if (input_->PushKey(DIK_LSHIFT)) {
	//	degree.y -= kCharacterSpeed;
	//}

	//if (input_->PushKey(DIK_S)) {
	//	degree.z -= kCharacterSpeed;
	//} else if (input_->PushKey(DIK_W)) {
	//	degree.z += kCharacterSpeed;
	//}

	//const float kRotSpeed = 0.02f;
	//if (input_->PushKey(DIK_Q)) {
	//	worldTransform_.rotation_.y -= kRotSpeed;
	//} else if (input_->PushKey(DIK_E)) {
	//	worldTransform_.rotation_.y += kRotSpeed;
	//}

	worldTransform_.translation_.x += degree.x;
	worldTransform_.translation_.y += degree.y;
	worldTransform_.translation_.z += degree.z;
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
	gauge_->Draw(viewProjection);
}

void Player::DrawPrimitive() { 
	gauge_->DrawBox();
	Collider::DrawCollider();
}
