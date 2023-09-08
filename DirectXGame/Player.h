#pragma once
#include "Base.h"
#include "Input.h"
#include "Collider.h"
#include "Model.h"
#include "Gauge.h"

class PlayerCamera;
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
	void SetPlayerCamera(PlayerCamera* camera) { playerCamera_ = camera; };

private:
	WorldTransform worldTransform_;
	Vector3 colliderPos_;
	Vector3 rotationSpeed_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	float radius_ = 11.0f;
	bool showCollider_ = true;
	const char* name_;
	Gauge* gauge_;
	PlayerCamera* playerCamera_ = nullptr;

	//Gamepad
	XINPUT_STATE joyState;
};
