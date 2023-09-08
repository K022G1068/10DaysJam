#include "Cam.h"
#include <cassert>
#include "ImGuiManager.h"

void Cam::Initialize() {
	worldTransform_.Initialize();
	viewProjection_.Initialize();
}

void Cam::Update() {
	ImGui::Begin("cam");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, .01f);
	ImGui::DragFloat3("rot", &worldTransform_.rotation_.x, .01f);
	ImGui::End();
	worldTransform_.UpdateMatrix();
	//viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	viewProjection_.TransferMatrix();
}
