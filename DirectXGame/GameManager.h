#pragma once
#include <cstdlib>
#include <ctime>
#include "Collider.h"
#include "Sprite.h"

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

	char directory_[32];
	//Texture
	uint32_t textureHandle_[9] = {0u};
	Sprite* UI_ = nullptr;
	Sprite* number1_ = nullptr;
	Sprite* number2_ = nullptr;
};
