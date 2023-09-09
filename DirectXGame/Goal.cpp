#include "Goal.h"

void Goal::Initialize(Model* model, Vector3& goalPosition, ViewProjection& viewProjection) {
	assert(model);
	modelGoal_ = model;
	BaseInit(viewProjection, showCollider_, name_);
	worldTransform_.Initialize();
	worldTransform_.translation_ = goalPosition;

	//Collider
	Vector3 colliderPos(0, 15.0f, 0.0f);
	Collider::BaseInit(viewProjection, showCollider_, name_);
	Collider::SetCollider(colliderPos, radius_);
	Collider::SetColliderParent(&worldTransform_);

	//Attribute
	SetAttribute(kCollisionAttributeEnemy);
	SetMaskAttribute(kCollisionAttributePlayer);
}

void Goal::Update() {
	ImGui::Begin("Goal ImGui");
	ImGui::Text("Goal Count ", goalieList_.size());
	ImGui::End();

	Collider::OnUpdate();
	worldTransform_.UpdateMatrix(); 
}

void Goal::Draw(ViewProjection& viewProjection) {
	modelGoal_->Draw(worldTransform_, viewProjection);
}

void Goal::DrawPrimitive() { 
	Collider::DrawCollider();
}

void Goal::OnCollision() {
	TurnRED();
	//auto it = std::find(goalieList_.begin(), goalieList_.end(), object_);
	//if (it != goalieList_.end()) {
	//	// Element found in the list
	//	return;
	//} else {
	//	// Element not found in the list
	//	goalieList_.push_back(object_);
	//}
	
}

void Goal::SetColliderPosition() {}

Vector3 Goal::GetWorldPosition() { return Vector3(); }

Goal::~Goal() {}
