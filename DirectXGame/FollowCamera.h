#pragma once
#define ROTATION_LIMITY 0.2F
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "ImGuiManager.h"
#include "MathUtility.h"

class FollowCamera {
public:
	void Initialize();
	void Update();
	void Reset();
	void SetTarget(const WorldTransform* target) { target_ = target; };
	const ViewProjection& GetViewProjection() { return viewProjection_; };

private:
	ViewProjection viewProjection_;
	const WorldTransform* target_ = nullptr;

	// Gamepad
	XINPUT_STATE joyState;
};
