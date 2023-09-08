#pragma once
#include "PrimitiveDrawer.h"
#include "WorldTransform.h"
#include "Model.h"
#include <cassert>

class PlayerCamera;
class Gauge {
public:
	void Initialize(Model* model, Vector3& pos, ViewProjection& viewProjection, float radius);
	void SetCamera(PlayerCamera* camera) { camera_ = camera; };
	void Update();
	void SetParent(const WorldTransform* parent);
	void Draw(ViewProjection& viewProjection);
	void SetName(const char* name) { name_ = name; };
	void DrawBox();

private:
	Vector4 WHITE_ = {1.0f, 1.0f, 1.0f, 1.0f};
	Vector4 RED_ = {1.0f, 0.0f, 0.0f, 1.0f};
	PlayerCamera* camera_ = nullptr;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	Vector3 scale_ = {5.4f, 0.5f, 0.1f};
	Vector3 offset_;
	float radius_;
	float width_ = 3.0f;
	const char* name_;
	uint32_t gaugeTexureHandle_ = 0;
};
