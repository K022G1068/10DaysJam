#include "Stage.h"
#include <math.h>
#include "ImGuiManager.h"

void Stage::Initialize() {
	model_ = Model::CreateFromOBJ("Stage", true);
	theta_ = .25;
	worldTransform_.Initialize();
	worldTransform_.translation_.y = .0f;
}

void Stage::Update() { worldTransform_.UpdateMatrix(); }

float Stage::GetGrandPosY(Vector3 objPos) {
	ImGui::Begin("stageY");
	ImGui::Text("PlayerPos %f %f %f", objPos.x, objPos.y, objPos.z);
	ImGui::Text(
	    "y %f", (float)sqrtf(powf(objPos.x, 2.0f) + powf(objPos.y, 2.0f)) * .26794919243112f);
	ImGui::End();
	return (float)sqrtf(powf(objPos.x, 2.0f) + powf(objPos.z, 2.0f)) * .26794919243112f;
}

void Stage::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }

Stage::~Stage() {}
