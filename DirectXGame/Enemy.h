#pragma once
#define STOP_MIN 60.0f
#define STOP_MAX 180.0f

#include "Base.h"
#include "Input.h"
#include "Collider.h"
#include "Model.h"
#include "Gauge.h"
#include <list>
#include "Dash.h"
#include <cstdlib>
#include <ctime>

enum class Phase {
	ApproachGoal,
	Stop,
	ApproachSpot,
	ApproachEnemy,
};
class Goal;
class Spot;
class Enemy;
class Player;

class BaseEnemyState{
public:
	virtual void Update(Enemy* e) = 0;
	void GetSpotDistance(Enemy* e);
	void GetEnemyDistance(Enemy* e);
	void Move(Vector3 velocity, Enemy* e);
	virtual ~BaseEnemyState() = default;

protected:
	Vector3 goalPos_;
	std::list<Vector3> spotPos_;
	std::list<Enemy*> enemies_;
	std::list<Enemy*> enemiesLowRotation_;
	Vector3 toGoal_ = {0, 0, 0};
	Vector3 toSpot_ = {0, 0, 0};
	Vector3 toEnemy_ = {0, 0, 0};
	Vector3 velocity_ = {0, 0, 0};
	Vector3 nearestSpotPos_ = {0, 0, 0};
	Vector3 nearestEnemyPos_ = {0, 0, 0};
	Vector3 playerPos_ = {0, 0, 0};
	Vector3 playerRotationSpeed_ = {0,0,0};
	int stopTime_ = 0;
	int countTime_ = 0;
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

class EnemyStateNothing : public BaseEnemyState {
public:
	void Update(Enemy* e) override;
};

class Enemy : public Collider
{
public:
	void Initialize(
	    Model* model, Vector3& enemyPosition, ViewProjection& viewProjection,
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
	std::list<Vector3> GetSpot() { return spotPos_; };
	std::list<Enemy* > GetEnemies() { return enemies_; };
	const WorldTransform& GetWorldTransform() { return worldTransform_; };
	Vector3 GetWorldPosition() override;
	void SetRandomNumber(int number);
	int GetRandomNumber() { return random_number; };
	const char* GetName() { return name_; };
	void GetEnemyDistance() { state_->GetEnemyDistance(this); };
	Player* GetPlayer() { return player_; };
	void GetRandomRotation(int number);
	int GetStopTime() { return stopTime_; }; 
	int GetPercetageDash() { return percentageDash_; };


	//Setter
	void SetColliderPosition();
	void SetGoal(Vector3 goal) { goalPos_ = goal; };
	void SetSpot(Vector3 spot) { spotPos_.push_back(spot); };
	void SetEnemies(std::list<Enemy*> enemy) { enemies_ = enemy; };
	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	};
	void SetVelocity(Vector3 velocity) { velocity_ = velocity; };
	void FlyingToGoal();
	void SetPlayer(Player* player) { player_ = player; };

private:
	WorldTransform worldTransform_;
	const ViewProjection* viewProjection_ = nullptr;
	Vector3 colliderPos_;
	Model* model_ = nullptr;
	Gauge* gauge_ = nullptr;
	Model* gaugeModel_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Spot* spot_ = nullptr;
	Dash* dash_ = nullptr;
	float radius_ = 11.0f;
	bool showCollider_ = true;
	bool isFlying_ = false;
	const char* name_;
	float outerRadius_; //Radius to scan for nearby object
	Vector3 velocity_ = {0.0f, 0.0f, 0.0f};
	Vector3 totalCollisionDash = {0, 0, 0};
	BaseEnemyState* state_;
	Player* player_ = nullptr;
	Vector3 goalPos_ = {0, 0, 0};
	Vector3 spotPos2_ = {0, 0, 0};
	std::list<Vector3> spotPos_;
	float collisionPower_ = 0.0f;
	Vector3 toGoal_ = {0, 0, 0};
	int stopTime_ = 0;

	Easing easing_;
	Easing easing2_;

	//Enemy state percetage
	int percentageDash_ = 50;
	int percentageSpot_ = 50;
	int random_number;

	//enemy list
	std::list<Enemy*> enemies_;
};
