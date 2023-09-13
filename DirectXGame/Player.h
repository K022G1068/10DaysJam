#pragma once
#define GOAL_DEEPEST 70.0f
#define MIN_CHARACTER_SPEED 0.5F
#define MAX_CHARACTER_SPEED 0.75F

#include "Base.h"
#include "Input.h"
#include "Collider.h"
#include "Model.h"
#include "Gauge.h"
#include "Dash.h"
#include "Stage.h"

class Goal;
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
	void SetStage(Stage* stage) { stage_ = stage; };
	void SetPositionLerp(Vector3 pos) override;
	float GetRandomRotationDegree();
	void SetGoal(Goal* goal) { goal_ = goal; };

private:
	WorldTransform worldTransform_;
	const ViewProjection* viewProjection_ = nullptr;
	Vector3 colliderPos_;
	Model* model_ = nullptr;
	Stage* stage_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	float radius_ = 5.5f;
	bool showCollider_ = true;
	bool isFlying_ = false;
	const char* name_;
	Gauge* gauge_ = nullptr;
	Dash* dash_ = nullptr;
	Goal* goal_ = nullptr;
	Easing easing_;
	Easing easing2_;
	Vector3 goalPos_ = {0, 0, 0};
	Vector3 toGoal_ = {0, 0, 0};
	Vector3 velocity_ = {0, 0, 0};
	Vector3 collisionVelocity_ = {0, 0, 0};
	Vector3 totalCollisionDash = {0, 0, 0};
	float collisionPower_ = 0.0f;
	float kCharacterSpeed = 0.5f;
	Vector3 acceleration_ = {0, 0, 0};
	int currentGoalCount = 0;
	//Gamepad
	XINPUT_STATE joyState_;
	XINPUT_STATE prevjoyState_;
};
