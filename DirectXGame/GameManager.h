#pragma once
#include <cstdlib>
#include <ctime>
#include "Collider.h"
#include "Sprite.h"
#include "MathUtility.h"

class Goal;
class GameManager {
public:
	void Initialize();
	void Update();
	void Restart();
	void GetGoal(Goal* goal) { goal_ = goal; };
	int GetGoalNumber() { return goalNumber_; };
	void Draw();

private:
	int goalNumber_;
	bool goalNumberFull_ = false;
	bool win_ = false;
	bool lose_ = false;
	Goal* goal_;
	std::vector<Collider*> goalieList_;
	Vector2 baseSize_ = {1280, 720};
	Vector2 basePos_ = {0, 0};
	Vector2 goalNumberUIPos_ = {-110, -30};
	Vector2 goalNumberUISize_ = {350, 196};


	char directory_[32];
	//Texture
	uint32_t textureHandle_[9] = {0u};
	Sprite* UI_ = nullptr;
	Sprite* goalNumberUI_ = nullptr;
	Sprite* currentNumberUI_ = nullptr;
	int countTime_ = 0;
};
