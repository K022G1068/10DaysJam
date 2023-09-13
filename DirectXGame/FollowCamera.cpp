#include "FollowCamera.h"

void FollowCamera::Initialize() { 
	viewProjection_.Initialize(); 
	viewProjection_.rotation_.x = 0.2f;
}

void FollowCamera::Update() { 
	Vector3 rotation = {0, 0, 0};
	const float kCharacterRotationSpeed = 0.05f;
	if (target_)
	{
		Vector3 offset = {0.0f, 10.0f, -55.0f};

		Matrix4x4 rotationX = MakeRotationMatrixX(viewProjection_.rotation_.x);
		Matrix4x4 rotationY = MakeRotationMatrixY(viewProjection_.rotation_.y);
		Matrix4x4 rotationZ = MakeRotationMatrixZ(viewProjection_.rotation_.z);

		Matrix4x4 matrixRotate = rotationX * rotationY * rotationZ;

		offset = TransformNormal(offset, matrixRotate);

		viewProjection_.translation_ = target_->translation_ + offset;
	}

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		rotation = {
		    (float)joyState.Gamepad.sThumbRY / SHRT_MAX,
		    (float)joyState.Gamepad.sThumbRX / SHRT_MAX , 0.1f
		};

		
		rotation = Normalize(rotation) * kCharacterRotationSpeed;
		rotation.z = 0.0f;
	} else {
		ImGui::Text("No controller detected");
	}
	viewProjection_.rotation_ += rotation;
	
	if (viewProjection_.rotation_.x >= 0.5f)
	{
		viewProjection_.rotation_.x = 0.5f;
	}
	if (viewProjection_.rotation_.x <= -0.2f) {
		viewProjection_.rotation_.x = -0.2f;
	}


	viewProjection_.UpdateMatrix();
}

void FollowCamera::Reset() { 
	viewProjection_.rotation_.x = 0.2f;
	viewProjection_.rotation_.y = 0.0f;
	viewProjection_.rotation_.z = 0.0f;
}
