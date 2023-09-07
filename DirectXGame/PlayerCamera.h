#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ImGuiManager.h"
#include <vector>
#include "Input.h"
#include "MathUtility.h"

class PlayerCamera {
public:
	~PlayerCamera();
	void Initialize(Vector3 worldPos, Vector3 worldRot, ViewProjection& viewProjection);
	void Update();
	const ViewProjection& GetViewProjection() { return viewProjection_; };
	const WorldTransform& GetWorldTransform() { return worldTransform_; };
	void CameraMovement();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Input* input_ = nullptr;
};
