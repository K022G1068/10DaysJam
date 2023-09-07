#include "PlayerCamera.h"

PlayerCamera::~PlayerCamera() {}

void PlayerCamera::Initialize(Vector3 worldPos, Vector3 worldRot, ViewProjection& viewProjection) {
	worldTransform_.Initialize();
	worldTransform_.translation_ = worldPos;
	worldTransform_.rotation_ = worldRot;
	viewProjection_.Initialize();
	input_ = Input::GetInstance();
}

void PlayerCamera::Update() {
	
	worldTransform_.UpdateMatrix();
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
}

void PlayerCamera::CameraMovement() {
	
	Vector3 move = {0, 0, 0};

	 const float kCharacterSpeed = 0.2f;

	 if (input_->PushKey(DIK_A)) {
		move.x -= kCharacterSpeed;
	 } else if (input_->PushKey(DIK_D)) {
		move.x += kCharacterSpeed;
	 }

	 if (input_->PushKey(DIK_SPACE))
	{
		//move.y += kCharacterSpeed;
	 } else if (input_->PushKey(DIK_LSHIFT)) {
		move.y -= kCharacterSpeed;
	 }

	 if (input_->PushKey(DIK_S)) {
		move.z -= kCharacterSpeed;
	 } else if (input_->PushKey(DIK_W)) {
		move.z += kCharacterSpeed;
	 }

	 const float kRotSpeed = 0.02f;
	 if (input_->PushKey(DIK_Q)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	 } else if (input_->PushKey(DIK_E)) {
		worldTransform_.rotation_.y += kRotSpeed;
	 }

	 worldTransform_.translation_.x += move.x;
	 worldTransform_.translation_.y += move.y;
	 worldTransform_.translation_.z += move.z;
}
