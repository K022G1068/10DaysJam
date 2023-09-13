#include "PlayerCamera.h"

PlayerCamera::~PlayerCamera() {}

void PlayerCamera::Initialize(Vector3 worldPos, Vector3 worldRot) {
	worldTransform_.Initialize();
	worldTransform_.translation_ = worldPos;
	worldTransform_.rotation_ = worldRot;
	viewProjection_.Initialize();
	input_ = Input::GetInstance();
}

void PlayerCamera::Update() {
	CameraMovement();
	worldTransform_.UpdateMatrix();
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	
	//ImGui
	//ImGui::Begin("Camera");
	float sliderTrans[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	//ImGui::DragFloat3("Translate", sliderTrans, 0.01f);
	worldTransform_.translation_ = {sliderTrans[0], sliderTrans[1], sliderTrans[2]};
	float sliderRot[3] = {
	    worldTransform_.rotation_.x, worldTransform_.rotation_.y, worldTransform_.rotation_.z};
	//ImGui::DragFloat3("Rotate", sliderRot, 0.01f);
	worldTransform_.rotation_ = {sliderRot[0], sliderRot[1], sliderRot[2]};
	//ImGui::End();
}

Vector3 PlayerCamera::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void PlayerCamera::CameraMovement() {

	Vector3 move = {0, 0, 0};
	Vector3 rotation = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;
	const float kCharacterRotationSpeed = 0.05f;
	 if (Input::GetInstance()->GetJoystickState(0, joyState))
	 {
		 move = {
		     (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed, 0.0f,
		     (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed};

		 rotation = {
		     (float)joyState.Gamepad.sThumbRY / SHRT_MAX * kCharacterRotationSpeed,
		     (float)joyState.Gamepad.sThumbRX / SHRT_MAX * kCharacterRotationSpeed, 
		     0.0f};

		 //move = Normalize(move) * kCharacterSpeed;
	 }
	 else
	 {
		 //ImGui::Text("No controller detected");
	 }


	 worldTransform_.translation_ += move;
	 worldTransform_.rotation_ += rotation;
	// if (input_->PushKey(DIK_A)) {
	//	move.x -= kCharacterSpeed;
	// } else if (input_->PushKey(DIK_D)) {
	//	move.x += kCharacterSpeed;
	// }

	// if (input_->PushKey(DIK_SPACE))
	//{
	//	//move.y += kCharacterSpeed;
	// } else if (input_->PushKey(DIK_LSHIFT)) {
	//	move.y -= kCharacterSpeed;
	// }

	// if (input_->PushKey(DIK_S)) {
	//	move.z -= kCharacterSpeed;
	// } else if (input_->PushKey(DIK_W)) {
	//	move.z += kCharacterSpeed;
	// }

	// const float kRotSpeed = 0.02f;
	// if (input_->PushKey(DIK_Q)) {
	//	worldTransform_.rotation_.y -= kRotSpeed;
	// } else if (input_->PushKey(DIK_E)) {
	//	worldTransform_.rotation_.y += kRotSpeed;
	// }

	// worldTransform_.translation_.x += move.x;
	// worldTransform_.translation_.y += move.y;
	// worldTransform_.translation_.z += move.z;
}
