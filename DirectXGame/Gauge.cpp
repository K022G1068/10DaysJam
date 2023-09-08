#include "Gauge.h"

void Gauge::Initialize(Model* model, Vector3& pos, ViewProjection& viewProjection, float radius) {
	assert(model);	
	
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection);
	radius_ = radius + radius/2;
	gaugeTexureHandle_ = TextureManager::Load("green1x1.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	worldTransform_.scale_ = scale_;
	model_ = model;
}

void Gauge::Update() { 
	worldTransform_.scale_ = scale_;
	Matrix4x4 rotMat = MakeRotationMatrixY(rotation_);
	worldTransform_.rotation_ = TransformNormal(worldTransform_.rotation_, rotMat);
	worldTransform_.UpdateMatrix();
}

void Gauge::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

void Gauge::Draw(ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection, gaugeTexureHandle_);
}

void Gauge::DrawBox() {
	Vector3 corner[4];
	// Top left
	corner[0] = {
	    worldTransform_.matWorld_.m[3][0] - radius_ / 2,
	    worldTransform_.matWorld_.m[3][1] + width_ / 2, worldTransform_.matWorld_.m[3][2]};
	// Top right
	corner[1] = {
	    worldTransform_.matWorld_.m[3][0] + radius_ / 2,
	    worldTransform_.matWorld_.m[3][1] + width_ / 2, worldTransform_.matWorld_.m[3][2]};
	// Bottom left
	corner[2] = {
	    worldTransform_.matWorld_.m[3][0] - radius_ / 2,
	    worldTransform_.matWorld_.m[3][1] - width_ / 2, worldTransform_.matWorld_.m[3][2]};
	// Bottom right
	corner[3] = {
	    worldTransform_.matWorld_.m[3][0] + radius_ / 2,
	    worldTransform_.matWorld_.m[3][1] - width_ / 2, worldTransform_.matWorld_.m[3][2]};
	
	PrimitiveDrawer::GetInstance()->DrawLine3d(corner[0], corner[1], WHITE_);
	PrimitiveDrawer::GetInstance()->DrawLine3d(corner[1], corner[3], WHITE_);
	PrimitiveDrawer::GetInstance()->DrawLine3d(corner[2], corner[3], WHITE_);
	PrimitiveDrawer::GetInstance()->DrawLine3d(corner[2], corner[0], WHITE_);

}
