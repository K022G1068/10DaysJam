#pragma once
#include "Base.h"
#include "Input.h"
#include "Collider.h"
#include "Model.h"
#include "Gauge.h"
#include <list>

enum class Phase {
	ApproachGoal,
	Stop,
	ApproachSpot,
	ApproachEnemy,
};
class Goal;
class Spot;
class Enemy;

class BaseEnemyState{
public:
	virtual void Update(Enemy* e) = 0;
	void GetDistance();
	virtual ~BaseEnemyState() = default;

protected:
	Vector3 goalPos_;
	std::list<Vector3> spotPos_;
	Vector3 toGoal_ = {0, 0, 0};
	Vector3 toSpot_ = {0, 0, 0};
	Vector3 velocity_ = {0, 0, 0};
};

class EnemyStateApproachGoal : public BaseEnemyState {
public:
	void Update(Enemy* e) override;
};

class EnemyStateStop : public BaseEnemyState {
public:
	void Update(Enemy* e) override;
};

class EnemyStateApproachEnemy : public BaseEnemyState {
public:
	void Update(Enemy * e) override;
};

class EnemyStateApproachSpot : public BaseEnemyState {
public:
	void Update(Enemy * e) override;
};

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
	
	//Enemy state
	void ChangeState(BaseEnemyState* enemyState);
	void ApproachGoal();
	void Stop();
	void ApproachSpot();
	void ApproachEnemy();

	//Getter
	Vector3 GetGoal() { return goalPos_; };
	std::list<Vector3*> GetSpot() { return spotPos_; };
	const WorldTransform& GetWorldTransform() { return worldTransform_; };
	Vector3 GetWorldPosition() override;

	//Setter
	void SetColliderPosition();
	void SetGoal(Vector3 goal) { goalPos_ = goal; };
	void SetSpot(Spot* spot) { spot_ = spot; };
	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	};
	void SetVelocity(Vector3 velocity) { velocity_ = velocity; };

private:
	WorldTransform worldTransform_;
	const ViewProjection* viewProjection_ = nullptr;
	Vector3 colliderPos_;
	Vector3 rotationSpeed_;
	Model* model_ = nullptr;
	Gauge* gauge_ = nullptr;
	Model* gaugeModel_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Spot* spot_ = nullptr;
	float radius_ = 11.0f;
	bool showCollider_ = true;
	const char* name_;
	float outerRadius_; //Radius to scan for nearby object
	Vector3 velocity_ = {0.0f, 0.0f, 0.0f};
	BaseEnemyState* state_;

	Vector3 goalPos_ = {0, 0, 0};
	std::list<Vector3*> spotPos_;
	bool isGoal = false;
};
