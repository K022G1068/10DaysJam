#include "Spot.h"

void Spot::Initialize(Model* model, Vector3& spotPosition, ViewProjection& viewProjection) {
	assert(model);
	modelSpot_ = model;
	BaseInit(viewProjection, showCollider_, name_);
	worldTransform_.Initialize();
	worldTransform_.translation_ = spotPosition;

	// Collider
	Vector3 colliderPos(0.0f, 0.0f, 0.0f);
	Collider::BaseInit(viewProjection, showCollider_, name_);
	Collider::SetCollider(colliderPos, radius_);
	Collider::SetColliderParent(&worldTransform_);

	// Attribute
	SetAttribute(kCollisionAttributeSpot);
	SetMaskAttribute(kCollisionAttributePlayer);
}

void Spot::Update() {
	Collider::OnUpdate();
	worldTransform_.UpdateMatrix();
}

void Spot::Draw(ViewProjection& viewProjection) { 
	modelSpot_->Draw(worldTransform_ ,viewProjection); 
}

void Spot::DrawPrimitive() { 
	Collider::DrawCollider();
}

void Spot::IncreaseRotationSpeed(Collider* collider) {
	Vector3 rotationspeed = collider->GetRotationSpeed();
	ImGui::Text("Collider %f %f %f", rotationspeed);
	rotationspeed += 0.0001f;
	rotationspeed.x = 0.0f;
	rotationspeed.z = 0.0f;
	collider->SetRotationSpeed(rotationspeed);
	Vector3 direction = {0, 0, 0};
	if (rotationspeed.y >= MAX_ROTATION)
	{
		ImGui::Text("Spot countime %d", countTime_);
		countTime_++;
		SetRandomDirection();
		if (countTime_ >= MAX_STAY_TIME)
		{
			countTime_ = 0;
			Matrix4x4 rotMat = MakeRotationMatrixY(degree_);
			direction = TransformNormal(worldTransform_.translation_, rotMat);
			direction = Normalize(direction) * 5.0f;
			direction.y = 0.0f;
			collider->SetSpotVelocity(direction);
		}
		//collider->SetVelocity({0,0,0});
	}
}

void Spot::SetRandomDirection() {
	std::srand(static_cast<unsigned>(std::time(nullptr)) + 1000);
	degree_ = (std::rand() % 629) / 100.0f;
}

void Spot::OnCollision() { 
	TurnRED();
	Collider* collidedObject = GetCollidedCollider();
	IncreaseRotationSpeed(collidedObject);
}

Vector3 Spot::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Spot::~Spot() {}
