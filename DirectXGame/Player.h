#pragma once
#include "Base.h"
#include "Input.h"
#include "Collider.h"
#include "Model.h"
#include "Gauge.h"
#include "Dash.h"

class Player : public Collider
{
public:
	void Initialize(
	    Model* model, Vector3& playerPosition,
	    ViewProjection& viewProjection, const char* name);
	void InitializeGauge(Model* gaugeModel, Model* gaugeModelBox);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void DrawPrimitive();
	void SetParent(const WorldTransform* parent);
	void Move();
	~Player();
	void OnCollision() override;
	void SetColliderPosition();
	Vector3 GetWorldPosition() override;
	const WorldTransform& GetWorldTransform() override { return worldTransform_; };
	//void SetPlayerCamera(PlayerCamera* camera) { playerCamera_ = camera; };
	void SetViewProjection(const ViewProjection* viewProjection) { viewProjection_ = viewProjection; };
	void SetGoal(Vector3 goal) { goalPos_ = goal; };
	void FlyingToGoal();
	const char* GetName() override { return name_; };
	void SetVelocity(Vector3 velocity) override { velocity_ = velocity; };

private:
	WorldTransform worldTransform_;
	const ViewProjection* viewProjection_ = nullptr;
	Vector3 colliderPos_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	float radius_ = 11.0f;
	bool showCollider_ = true;
	bool isFlying_ = false;
	const char* name_;
	Gauge* gauge_;
	Dash* dash_;
	Easing easing_;
	Easing easing2_;
	Vector3 goalPos_ = {0, 0, 0};
	Vector3 toGoal_ = {0, 0, 0};
	Vector3 velocity_ = {0, 0, 0};
	Vector3 collisionVelocity_ = {0, 0, 0};
	Vector3 totalCollisionDash = {0, 0, 0};
	float collisionPower_ = 0.0f;
	const float kCharacterSpeed = 0.5f;
	//Gamepad
	XINPUT_STATE joyState_;
	XINPUT_STATE prevjoyState_;
};
