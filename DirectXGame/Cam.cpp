#include "Cam.h"
#include "ImGuiManager.h"
#include <cassert>

void Cam::Initialize(Input*input) {
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	input_ = input;

	worldTransform_.rotation_.x = 1.57f;
	worldTransform_.translation_.y = 500.f;

	worldTransform_.UpdateMatrix();
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	viewProjection_.TransferMatrix();
}

void Cam::Update() {
	worldTransform_.translation_.z += input_->GetWheel()*.01f;
	if (input_->IsPressMouse(2)) {
		worldTransform_.translation_.x -= (float)input_->GetMouseMove().lX*.01f;
		worldTransform_.translation_.y += (float)input_->GetMouseMove().lY*.01f;
		worldTransform_.translation_.z += (float)input_->GetMouseMove().lZ*.01f;
	}
	if (input_->IsPressMouse(1)) {
		worldTransform_.rotation_.y += (float)input_->GetMouseMove().lX * .001f;
		//worldTransform_.rotation_.z += (float)input_->GetMouseMove().lY * .001f;
		worldTransform_.rotation_.z += (float)input_->GetMouseMove().lZ * .001f;
	}

	ImGui::Begin("cam");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, .01f);
	ImGui::DragFloat3("rot", &worldTransform_.rotation_.x, .01f);
	ImGui::End();

	worldTransform_.UpdateMatrix();
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	viewProjection_.TransferMatrix();
}
