#include "FollowCamera.h"

void FollowCamera::Initialize() { 
	viewProjection_.Initialize(); 
}

void FollowCamera::Update() { 
	Vector3 rotation = {0, 0, 0};
	const float kCharacterRotationSpeed = 0.05f;
	if (target_)
	{
		Vector3 offset = {0.0f, 20.0f, -100.0f};

		Matrix4x4 rotationX = MakeRotationMatrixX(viewProjection_.rotation_.x);
		Matrix4x4 rotationY = MakeRotationMatrixY(viewProjection_.rotation_.y);
		Matrix4x4 rotationZ = MakeRotationMatrixZ(viewProjection_.rotation_.z);

		Matrix4x4 matrixRotate = rotationX * rotationY * rotationZ;

		offset = TransformNormal(offset, matrixRotate);

		viewProjection_.translation_ = target_->translation_ + offset;
	}

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		rotation = {
			0.0f,
		    (float)joyState.Gamepad.sThumbRX / SHRT_MAX * kCharacterRotationSpeed, 0.0f};

		
	} else {
		ImGui::Text("No controller detected");
	}
	viewProjection_.rotation_ += rotation;
	viewProjection_.UpdateMatrix();
}
