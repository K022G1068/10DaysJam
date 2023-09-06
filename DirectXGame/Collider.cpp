#include "Collider.h"
#include <cstdint>

void Collider::BaseInit(ViewProjection& viewProjection) {
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection);
}

void Collider::OnUpdate() {
	color_ = WHITE_;
}

void Collider::OnCollision() {}

void Collider::OnColliderCollision() { color_ = RED_; }

void Collider::SetCollider(Vector3& center, float radius) {
	colliderSphere_.sphereCenter = center;
	colliderSphere_.radius = radius;
}

bool Collider::SphereCollisionCheck(const ColliderSphere& s1, const ColliderSphere& s2) {
	Vector3 distanceVector = Subtract(s1.sphereCenter, s2.sphereCenter);
	float distanceSq = Dot(distanceVector, distanceVector);
	float sumRadius = s1.radius + s2.radius;
	return distanceSq <= (sumRadius * sumRadius);
}

void Collider::DrawCollider() {

	if (showCollider_) {
		float pi = 3.141592f;
		const uint32_t kSubdivision = 12;
		const float kLonEvery = pi * 2.0f / float(kSubdivision);
		const float kLatEvery = pi / float(kSubdivision);

		// Vector3 screenVertices[3]{};
		for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
			float lat = -pi / 2.0f + kLatEvery * latIndex;
			for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
				float lon = lonIndex * kLonEvery;
				Vector3 a = {
				    colliderSphere_.sphereCenter.x + colliderSphere_.radius * cosf(lat) * cosf(lon),
				    colliderSphere_.sphereCenter.y + colliderSphere_.radius * sinf(lat),
				    colliderSphere_.sphereCenter.z +
				        colliderSphere_.radius * cosf(lat) * sinf(lon)};

				Vector3 b = {
				    colliderSphere_.sphereCenter.x +
				        colliderSphere_.radius * cosf(lat + kLatEvery) * cosf(lon),
				    colliderSphere_.sphereCenter.y + colliderSphere_.radius * sinf(lat + kLatEvery),
				    colliderSphere_.sphereCenter.z +
				        colliderSphere_.radius * cosf(lat + kLatEvery) * sinf(lon),
				};

				Vector3 c = {
				    colliderSphere_.sphereCenter.x +
				        colliderSphere_.radius * cosf(lat + kLatEvery) * cosf(lon + kLonEvery),
				    colliderSphere_.sphereCenter.y + colliderSphere_.radius * sinf(lat + kLatEvery),
				    colliderSphere_.sphereCenter.z +
				        colliderSphere_.radius * cosf(lat + kLatEvery) * sinf(lon + kLonEvery),
				};
				PrimitiveDrawer::GetInstance()->DrawLine3d(a, b, color_);
				PrimitiveDrawer::GetInstance()->DrawLine3d(b, c, color_);
				PrimitiveDrawer::GetInstance()->DrawLine3d(a, c, color_);
			}
		}
	}
}
