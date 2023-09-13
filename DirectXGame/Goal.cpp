#include "Goal.h"

void Goal::Initialize(Model* model, Vector3& goalPosition, ViewProjection& viewProjection) {
	assert(model);
	modelGoal_ = model;
	BaseInit(viewProjection, showCollider_, name_);
	worldTransform_.Initialize();
	worldTransform_.translation_ = goalPosition;
	
	//Collider
	Vector3 colliderPos(0, 15.0f, 12.0f);
	Collider::BaseInit(viewProjection, showCollider_, name_);
	Collider::SetColliderParent(&worldTransform_);
	Collider::SetCollider(colliderPos, radius_);

	//Attribute
	SetAttribute(kCollisionAttributeGoal);
	SetMaskAttribute(kCollisionAttributeAny);
}

void Goal::Update() {
	ImGui::Begin("Goal ImGui");
	ImGui::Text(
	    "collider world pos %s: %f %f %f", name_, Collider::GetColliderWorldPosition().x,
	    Collider::GetColliderWorldPosition().y, Collider::GetColliderWorldPosition().z);
	ImGui::Text("Goal Count %d", goalieList_.size());
	ImGui::Text("Koma Count %d", komaCount_);
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
	
	Collider* collidedObject = GetCollidedCollider();

	auto it = std::find(goalieList_.begin(), goalieList_.end(), collidedObject);
	if (it != goalieList_.end()) {
		// Element found in the list
		ImGui::Text("Collided Object is in the list ");
		return;
	} else {
		// Element not found in the list
		komaCount_++;
		goalieList_.push_back(collidedObject);
		collidedObject->SetPositionLerp({0, -30.0f, 250.0f});
		ImGui::Text("Added collided object ");
	}
}

void Goal::SetColliderPosition() {}

Vector3 Goal::GetWorldPosition() { 
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Goal::SetPositionLerp(Vector3 pos) {
	worldTransform_.translation_ = Lerp(worldTransform_.translation_, pos, 0.2f);
}

Goal::~Goal() {}
