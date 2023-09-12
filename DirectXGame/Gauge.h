#pragma once
#define MAX_ROTATION 0.3f
#define MIN_ROTATION 0.06f
#define MAX_BAR 2.8f

#include "PrimitiveDrawer.h"
#include "WorldTransform.h"
#include "Model.h"
#include <cassert>
#include "MathUtility.h"

class PlayerCamera;
class Gauge {
public:
	void Initialize(Model* model, Model* modelBox, Vector3& pos, const ViewProjection* viewProjection, float radius);
	void GetCameraRotation(float rotation) { cameraRotation_ = rotation; };
	void GetRotation(Vector3 rotation) { rotation_ = rotation; };
	void Update();
	void SetPosition(Vector3& translation);
	void Draw(ViewProjection& viewProjection);
	void SetName(const char* name) { name_ = name; };
	void DrawBox();

private:
	Vector4 WHITE_ = {1.0f, 1.0f, 1.0f, 1.0f};
	Vector4 RED_ = {1.0f, 0.0f, 0.0f, 1.0f};
	PlayerCamera* camera_ = nullptr;
	WorldTransform worldTransform_;
	WorldTransform worldTransform2_;
	const ViewProjection* viewProjection_ = nullptr;
	Model* model_ = nullptr;
	Model* modelBox_ = nullptr;
	Vector3 scale_ = {3.5f, 0.2f, 0.1f};
	Vector3 scale2_ = {2.1f, 0.5f, 0.1f};
	Vector3 offset_;
	float radius_;
	float width_ = 3.0f;
	const char* name_;
	uint32_t gaugeTexureHandle_ = 0;
	float cameraRotation_;
	Vector3 rotation_;
};
