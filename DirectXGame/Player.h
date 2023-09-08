#pragma once
#include "Base.h"
#include "Input.h"
#include "Collider.h"
#include "Model.h"
#include "Gauge.h"
#include "Dash.h"

//class PlayerCamera;
class Player : public Collider
{
public:
	void Initialize(
	    Model* model, Model* gaugeModel, Vector3& playerPosition,
	    ViewProjection& viewProjection, const char* name);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void DrawPrimitive();
	void SetParent(const WorldTransform* parent);
	void Move();
	~Player();
	void OnCollision() override;
	void SetColliderPosition();
	Vector3 GetWorldPosition() override;
	const WorldTransform& GetWorldTransform() { return worldTransform_; };
	//void SetPlayerCamera(PlayerCamera* camera) { playerCamera_ = camera; };
	void SetViewProjection(const ViewProjection* viewProjection) { viewProjection_ = viewProjection; };

private:
	WorldTransform worldTransform_;
	const ViewProjection* viewProjection_ = nullptr;
	Vector3 colliderPos_;
	Vector3 rotationSpeed_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	float radius_ = 11.0f;
	bool showCollider_ = true;
	const char* name_;
	Model* mode_;
	Gauge* gauge_;
	Dash* dash_;

	//Gamepad
	XINPUT_STATE joyState_;
	XINPUT_STATE prevjoyState_;
};
