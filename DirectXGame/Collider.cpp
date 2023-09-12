#include "Collider.h"
#include <cstdint>

void Collider::BaseInit(ViewProjection& viewProjection, bool& show, const char* name) {
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection);
	worldTransform_.Initialize();
	showCollider_ = show;
	name_ = name;
}

void Collider::OnUpdate() {
	color_ = WHITE_;
	// ImGui
	ImGui::Checkbox(name_, &showCollider_);
	SetShowCollider(showCollider_);

	if (rotationSpeed_.y >= MAX_ROTATION)
	{
		rotationSpeed_.y = MAX_ROTATION;
	}
	if (rotationSpeed_.y <= MIN_ROTATION) 
	{
		rotationSpeed_.y = MIN_ROTATION;
	}

	worldTransform_.UpdateMatrix();
}

void Collider::OnCollision() {}

void Collider::OnCollisionEnter() {}

void Collider::OnColliderCollision() { color_ = RED_; }

Vector3 Collider::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Collider::SetCollider(Vector3& center, float radius) {
	worldTransform_.translation_ = center;
	colliderSphere_.radius = radius;
}

void Collider::SetColliderParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

bool Collider::SphereCollisionCheck(const Collider& s1, const Collider& s2) {
	Vector3 distanceVector = Subtract(worldTransform_.translation_, s2.worldTransform_.translation_);
	float distanceSq = Dot(distanceVector, distanceVector);
	float sumRadius = s1.colliderSphere_.radius + s2.colliderSphere_.radius;
	return distanceSq <= (sumRadius * sumRadius);
}

void Collider::DrawCollider() {

	if (showCollider_) {
		float pi = 3.141592f;
		const uint32_t kSubdivision = 6;
		const float kLonEvery = pi * 2.0f / float(kSubdivision);
		const float kLatEvery = pi / float(kSubdivision);

		// Vector3 screenVertices[3]{};
		for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
			float lat = -pi / 2.0f + kLatEvery * latIndex;
			for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
				float lon = lonIndex * kLonEvery;
				Vector3 a = {
				    worldTransform_.matWorld_.m[3][0] +
				        colliderSphere_.radius * cosf(lat) * cosf(lon),
				    worldTransform_.matWorld_.m[3][1] + colliderSphere_.radius * sinf(lat),
				    worldTransform_.matWorld_.m[3][2] +
				        colliderSphere_.radius * cosf(lat) * sinf(lon)};

				Vector3 b = {
				    worldTransform_.matWorld_.m[3][0] +
				        colliderSphere_.radius * cosf(lat + kLatEvery) * cosf(lon),
				    worldTransform_.matWorld_.m[3][1] +
				        colliderSphere_.radius * sinf(lat + kLatEvery),
				    worldTransform_.matWorld_.m[3][2] +
				        colliderSphere_.radius * cosf(lat + kLatEvery) * sinf(lon),
				};

				Vector3 c = {
				    worldTransform_.matWorld_.m[3][0] +
				        colliderSphere_.radius * cosf(lat + kLatEvery) * cosf(lon + kLonEvery),
				    worldTransform_.matWorld_.m[3][1] +
				        colliderSphere_.radius * sinf(lat + kLatEvery),
				    worldTransform_.matWorld_.m[3][2] +
				        colliderSphere_.radius * cosf(lat + kLatEvery) * sinf(lon + kLonEvery),
				};
				PrimitiveDrawer::GetInstance()->DrawLine3d(a, b, color_);
				PrimitiveDrawer::GetInstance()->DrawLine3d(b, c, color_);
				PrimitiveDrawer::GetInstance()->DrawLine3d(a, c, color_);
			}
		}
	}
}

Collider::~Collider() {}

