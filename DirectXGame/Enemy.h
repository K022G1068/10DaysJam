#pragma once
#include "Base.h"
#include "Input.h"
#include "Collider.h"
#include "Model.h"
#include "Gauge.h"

enum class Phase {
	ApproachGoal,
	Stop,
	ApproachSpot,
	ApproachEnemy,
};
class Goal;

class Enemy : public Collider
{
public:
	void Initialize(
	    Model* model, Vector3& playerPosition, ViewProjection& viewProjection,
	    const char* name);
	void InitializeGauge(Model* gaugeModel, Model* gaugeModelBox);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void DrawPrimitive();
	void Movement();
	~Enemy();
	void OnCollision() override;
	void SetColliderPosition();
	void SetGoal(const Goal* goal){};
	Vector3 GetWorldPosition() override;
	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	};
	
private:
	WorldTransform worldTransform_;
	const ViewProjection* viewProjection_ = nullptr;
	Vector3 colliderPos_;
	Vector3 rotationSpeed_;
	Model* model_ = nullptr;
	Gauge* gauge_ = nullptr;
	Model* gaugeModel_ = nullptr;
	uint32_t textureHandle_ = 0u;
	float radius_ = 11.0f;
	bool showCollider_ = true;
	const char* name_;
	float outerRadius_; //Radius to scan for nearby object
	Goal* goal_ = nullptr;
};
