#include "Gauge.h"

void Gauge::Initialize(
    Model* model, Model* modelBox, Vector3& pos, const ViewProjection* viewProjection,
    float radius) {
	assert(model);	
	PrimitiveDrawer::GetInstance()->SetViewProjection(viewProjection);
	viewProjection_ = viewProjection;
	radius_ = radius + radius/2;
	gaugeTexureHandle_ = TextureManager::Load("green1x1.png");
	modelBox_ = modelBox;
	worldTransform_.Initialize();
	worldTransform2_.Initialize();
	worldTransform_.translation_ = pos;
	worldTransform_.scale_ = scale_;
	worldTransform2_.translation_ = pos;

	worldTransform2_.scale_ = scale2_;
	model_ = model;
}

void Gauge::Update() { 
	
	scale_.x = (rotation_.y / MAX_ROTATION) * MAX_BAR;
	if (scale_.x <= MIN_ROTATION)
	{
		scale_.x = MIN_ROTATION;
	}
	if (scale_.x >= MAX_ROTATION)
	{
		scale_.x = MAX_BAR;
	}

	worldTransform_.scale_ = scale_;
	worldTransform_.rotation_.y = cameraRotation_ ;
	worldTransform2_.rotation_.y = cameraRotation_;
	worldTransform_.translation_.y += 1.315f * radius_;
	worldTransform2_.translation_.y += 1.3f * radius_;
	worldTransform_.UpdateMatrix();
	worldTransform2_.UpdateMatrix();
}

void Gauge::SetPosition(Vector3& translation) { 
	worldTransform_.translation_ = translation;
	worldTransform2_.translation_ = translation;
}

void Gauge::Draw(ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection, gaugeTexureHandle_);
	modelBox_->Draw(worldTransform2_, viewProjection);
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
