#pragma once
#include <cstdlib>
#include <ctime>
#include "Collider.h"

class Goal;
class GameManager {
public:
	void Initialize();
	void Update();
	void Restart();
	void GetGoal(Goal* goal) { goal_ = goal; };
	int GetGoalNumber() { return goalNumber_; };

private:
	int goalNumber_;
	bool goalNumberFull_ = false;
	bool win_ = false;
	bool lose_ = false;
	Goal* goal_;
	std::vector<Collider*> goalieList_;
};
