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
	void SetTimer();
	int GetTimer() { return stopTime_; };
	int GetCountTimer() { return countTime_; };
	void Move(Vector3 velocity, Enemy* e);
	virtual ~BaseEnemyState() = default;
	//bool GetNearEnemyBool() { return nearEnemy_; };

protected:
	Vector3 goalPos_;
	std::list<Vector3> spotPos_;
	std::list<Collider*> objects_;
	std::list<Collider*> objectLowRotation_;
	Vector3 toGoal_ = {0, 0, 0};
	Vector3 toSpot_ = {0, 0, 0};
	Vector3 toEnemy_ = {0, 0, 0};
	Vector3 velocity_ = {0, 0, 0};
	Vector3 nearestSpotPos_ = {0, 0, 0};
	Vector3 playerPos_ = {0, 0, 0};
	Vector3 playerRotationSpeed_ = {0,0,0};
	int stopTime_ = 300;
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
	//std::list<Enemy* > GetEnemies() { return enemies_; };
	const WorldTransform& GetWorldTransform() override { return worldTransform_; };
	Vector3 GetWorldPosition() override;
	void SetRandomNumber(int number);
	int GetRandomNumber() { return random_number; };
	const char* GetName() override { return name_; };
	void GetEnemyDistance() { state_->GetEnemyDistance(this); };
	void GetSpotDistance() { state_->GetSpotDistance(this); };
	Player* GetPlayer() { return player_; };
	void GetRandomRotation(int number);
	int GetStopTime() { return stopTime_; }; 
	int GetPercetageDash() { return percentageDash_; };
	bool GetNearEnemyBool() { return nearEnemy_; };
	const char* GetNearestEnemyName() { return nearestEnemyName_; };
	Vector3 GetNearestEnemyPosition() { return nearestEnemyPos_; };

	//Setter
	void SetColliderPosition();
	void SetGoal(Vector3 goal) { goalPos_ = goal; };
	void SetSpot(Vector3 spot) { spotPos_.push_back(spot); };
	//void SetEnemies(std::list<Enemy*> enemy) { enemies_ = enemy; };
	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	};
	void FlyingToGoal();
	void SetPlayer(Player* player) { player_ = player; };
	void SetVelocity(Vector3 velocity) override { velocity_ = velocity; };
	void SetNearEnemyBool(bool nearenemy) { nearEnemy_ = nearenemy; };
	void SetNearestEnemyName(const char* name) { nearestEnemyName_ = name; };
	void SetNearestEnemyPosition(Vector3 pos) { nearestEnemyPos_ = pos; };

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
	Vector3 collisionVelocity_ = {0, 0, 0};
	bool nearEnemy_ = false;

	Easing easing_;
	Easing easing2_;

	const char* nearestEnemyName_ = "";
	Vector3 nearestEnemyPos_ = {0, 0, 0};

	//Enemy state percetage
	int percentageDash_ = 50;
	int percentageSpot_ = 50;
	int random_number;

	//Object list
	//std::list<Enemy*> enemies_;
	//std::list<Collider*> objects_;
};
