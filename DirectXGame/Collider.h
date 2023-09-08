#pragma once
#include "ImGuiManager.h"
#include "MathUtility.h"
#include "PrimitiveDrawer.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include <vector>
#include <string>
#include "WorldTransform.h"

struct ColliderSphere {
	Vector3 sphereCenter;
	float radius;	
};

class Collider {
private:
	ColliderSphere colliderSphere_; // Collsion sphere
	bool showCollider_;             // Show collider or not
	Vector4 WHITE_ = {1.0f, 1.0f, 1.0f, 1.0f};
	Vector4 RED_ = {1.0f, 0.0f, 0.0f, 1.0f};
	Vector4 color_ = WHITE_;
	const char* name_ = " ";
	WorldTransform worldTransform_;

public:
	void BaseInit(ViewProjection& viewProjection, bool& show, const char* name);
	/// <summary>
	/// Get the collider
	/// </summary>
	/// <returns></returns>
	ColliderSphere GetCollider() { return colliderSphere_; };
	virtual void OnUpdate();
	/// <summary>
	/// On collision callback
	/// </summary>
	virtual void OnCollision();
	void OnColliderCollision();
	/// <summary>
	/// Get the world position
	/// </summary>
	/// <returns></returns>
	virtual Vector3 GetWorldPosition();
	/// <summary>
	/// Set the collider
	/// </summary>
	/// <param name="center"></param>
	/// <param name="radius"></param>
	void SetCollider(Vector3& center, float radius);
	void SetColliderParent(const WorldTransform* parent);
	/// <summary>
	/// Check the collision of 2 sphere
	/// </summary>
	/// <param name="s1"></param>
	/// <param name="s2"></param>
	/// <returns></returns>
	bool SphereCollisionCheck(const Collider& s1, const Collider& s2);
	/// <summary>
	/// Draw the collidersphere
	/// </summary>
	/// <param name="sphere"></param>
	/// <param name="viewProjectionMatrix"></param>
	/// <param name="viewportMatrix"></param>
	virtual void DrawCollider();
	bool GetShowCollider() { return showCollider_; };
	void SetShowCollider(bool set) { showCollider_ = set; };
	void TurnRED() { color_ = RED_; };
};
