#include "Stage.h"
#include "ImGuiManager.h"
#include <math.h>

void Stage::Initialize(int num, Vector3 Pos) {
	num_ = num;
	model_ = Model::CreateFromOBJ("Stage", true);
	for (int i = 0; i < 4; i++) {
		worldTransform_[i].Initialize();
		worldTransform_[i].translation_ = Pos;
		worldTransform_[i].rotation_.y += 1.57f * i;
		worldTransform_[i].scale_ = {5.0f,5.0f,5.0f};
		worldTransform_[i].UpdateMatrix();
	}
}

void Stage::Update() {
	ImGui::Begin("stageDraw");
	for (int i = 0; i < 4; i++) {
		//ImGui::Text("model%d", i);
		//ImGui::DragFloat("rot", &worldTransform_[i].rotation_.y, .01f);
		worldTransform_[i].UpdateMatrix();
	}
	ImGui::End();
}

float Stage::GetGrandPosY(Vector3 objPos) {
	return (float)sqrtf(powf(objPos.x, 2.0f) + powf(objPos.z, 2.0f)) * .26794919243112f;
}

void Stage::Draw(ViewProjection& viewProjection) {
	for (int i = 0; i < num_; i++) {
		model_->Draw(worldTransform_[i], viewProjection);
	}
}

ObjMode Stage::GetMode(Vector3 objPos) {
	float scl = (float)sqrtf(powf(objPos.x, 2.0f) + powf(objPos.z, 2.0f));
	ImGui::Begin("stage");
	ImGui::DragFloat("rad", &rad_, .01f);
	ImGui::Text("PlayerPos %f %f %f", objPos.x, objPos.y, objPos.z);
	ImGui::Text("playerVctr2/scl, %f, %f scl %f", objPos.x / scl, objPos.z / scl, scl);
	ImGui::Text("y %f", scl * .26794919243112f);
	ImGui::End();
	if (scl > rad_)
		return underGrand;
	switch (num_) {
	case 1:
		if ((objPos.x / scl <= -sqrtf(2.f) / 2 && objPos.z / scl >= -sqrtf(2.f) / 2) ||
		    (objPos.x / scl >= sqrtf(2.f) / 2 && objPos.z / scl >= -sqrtf(2.f) / 2))
			return underGrand;
		break;
	case 2:
		if ((objPos.x / scl >= -sqrtf(2.f) / 2 && objPos.z / scl >= sqrtf(2.f) / 2) ||
		    (objPos.x / scl >= sqrtf(2.f) / 2 && objPos.z / scl >= -sqrtf(2.f) / 2))
			return underGrand;
		break;
	case 3:
		if ((objPos.x / scl >= sqrtf(2.f) / 2 && objPos.z / scl <= sqrtf(2.f) / 2) ||
		    (objPos.x / scl >= sqrtf(2.f) / 2 && objPos.z / scl >= -sqrtf(2.f) / 2))
			return underGrand;
		break;
	}

	return onGrand;
}

Stage::~Stage() {}
