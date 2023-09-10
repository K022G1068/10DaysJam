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
	return (float)sqrtf(powf(objPos.x, 2.0f) + powf(objPos.z, 2.0f)) * .26794919243112f;
}

void Stage::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }

ObjMode Stage::GetMode(Vector3 objPos) {
	ImGui::Begin("stageY");
	ImGui::DragFloat("rad", &rad_, .01f);
	ImGui::Text("PlayerPos %f %f %f", objPos.x, objPos.y, objPos.z);
	ImGui::Text(
	    "y %f", (float)sqrtf(powf(objPos.x, 2.0f) + powf(objPos.y, 2.0f)) * .26794919243112f);
	ImGui::End();
	if ((float)sqrtf(powf(objPos.x, 2.0f) + powf(objPos.y, 2.0f)) > rad_)
		return underGrand;
	if ((float)sqrtf(powf(objPos.x, 2.0f) + powf(objPos.y, 2.0f)) < 3)
		return Goal;
	return onGrand;
}

Stage::~Stage() {}
