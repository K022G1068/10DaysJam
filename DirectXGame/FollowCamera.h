#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "ImGuiManager.h"
#include "MathUtility.h"

class FollowCamera {
public:
	void Initialize();
	void Update();
	void SetTarget(const WorldTransform* target) { target_ = target; };
	const ViewProjection& GetViewProjection() { return viewProjection_; };

private:
	ViewProjection viewProjection_;
	const WorldTransform* target_ = nullptr;

	// Gamepad
	XINPUT_STATE joyState;
};
