#include "Stage.h"
#include "ImGuiManager.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

void Stage::Initialize(int num, Vector3 Pos) {
	num_ = num;
	model_ = Model::CreateFromOBJ("Stage", true);
	for (int i = 0; i < 4; i++) {
		worldTransform_[i].Initialize();
		worldTransform_[i].translation_ = Pos;
		worldTransform_[i].rotation_.y += 1.57f * i;
		worldTransform_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransform_[i].UpdateMatrix();
	}
}

void Stage::Update() {
	// ImGui::Begin("stageDraw");
	for (int i = 0; i < 4; i++) {
		// ImGui::Text("model%d", i);
		// ImGui::DragFloat("rot", &worldTransform_[i].rotation_.y, .01f);
		worldTransform_[i].UpdateMatrix();
	}
	// ImGui::End();
}

float Stage::GetGrandPosY(Vector3 objPos) {
	ImGui::Begin("stage");
	ImGui::DragFloat3("correction", &correction.x, .01f);
	objPos -= correction;
	ImGui::End();
	return (float)sqrtf(powf(objPos.x, 2.0f) + powf(objPos.z, 2.0f)) * .26794919243112f;
}

void Stage::Draw(ViewProjection& viewProjection) {
	for (int i = 0; i < num_; i++) {
		model_->Draw(worldTransform_[i], viewProjection);
	}
}

ObjMode Stage::GetMode(Vector3 objPos) {
	ImGui::Begin("stage");
	ImGui::DragFloat3("correction", &correction.x, .01f);
	ImGui::Text("PlayerPosB %f %f %f", objPos.x, objPos.y, objPos.z);
	objPos -= correction;
	float scl = (float)sqrtf(powf(objPos.x, 2.0f) + powf(objPos.z, 2.0f));
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

Vector3 Stage::Respown() {
	Vector3 objPos;
	while (1) {
		srand((int)clock());
		objPos = {
		    (float)((rand() % (int)rad_ - rad_ / 2)), (float)((rand() % (int)rad_ - rad_ / 2)),
		    (float)((rand() % (int)rad_ - rad_ / 2))};
		float scl = (float)sqrtf(powf(objPos.x, 2.0f) + powf(objPos.z, 2.0f));
		if (scl > 10 && scl < rad_) {
			if (num_ == 1) {
				if ((objPos.x / scl >= -sqrtf(2.f) / 2 && objPos.z / scl <= -sqrtf(2.f) / 2) &&
				    (objPos.x / scl <= sqrtf(2.f) / 2 && objPos.z / scl <= -sqrtf(2.f) / 2))
					break;
			}
			if (num_ == 2) {
				if ((objPos.x / scl >= -sqrtf(2.f) / 2 && objPos.z / scl >= sqrtf(2.f) / 2) ||
				    (objPos.x / scl >= sqrtf(2.f) / 2 && objPos.z / scl >= -sqrtf(2.f) / 2))
					break;
			}
			if (num_ == 3) {
				if ((objPos.x / scl >= sqrtf(2.f) / 2 && objPos.z / scl <= sqrtf(2.f) / 2) ||
				    (objPos.x / scl >= sqrtf(2.f) / 2 && objPos.z / scl >= -sqrtf(2.f) / 2))
					break;
			}
		}
	}
	objPos += correction;
	return objPos;
}

Vector3 Stage::Sliding(Vector3 objPos) {
	objPos -= correction;
	float scl = (float)sqrtf(powf(objPos.x, 2.0f) + powf(objPos.z, 2.0f));
	scl *= -4;
	if (scl >= -36)
		return {.0f, .0f, .0f};
	return {objPos.x / scl, objPos.y / scl, objPos.z / scl};
}

Vector3 Stage::GetSpotRot(Vector3 objPos) { return objPos; }
