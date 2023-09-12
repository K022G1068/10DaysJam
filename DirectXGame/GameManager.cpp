#include "GameManager.h"
#include "Goal.h"

void GameManager::Initialize() {
	std::srand(static_cast<unsigned>(std::time(nullptr)) * 1000);
	goalNumber_ = (std::rand() % 7 + 1) ;
}

void GameManager::Update() { ;
	goalieList_ = goal_->GetGoalieList(); 
	ImGui::Begin("GameManager");
	ImGui::Text("Goal number %d", goalNumber_);
	ImGui::Text("Win %d", win_);
	ImGui::Text("Lose %d", lose_);
	ImGui::End();

	if (goalieList_.size() >= goalNumber_)
	{
		if (strcmp(goalieList_[goalNumber_ - 1]->GetName(), "Player") == 0) {
			win_ = true;
		} else {
			lose_ = true;
		}
	}
	
}

void GameManager::Restart() {}
