#pragma once
#define MAX_ROTATION 0.3f
#define MIN_ROTATION 0.06f
#include "ImGuiManager.h"
#include "MathUtility.h"
#include "PrimitiveDrawer.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include <vector>
#include <string>
#include "WorldTransform.h"
#include "CollisionConfig.h"
#include <list>

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
	const char* name_ = "";
	WorldTransform worldTransform_;
	uint32_t collisionAttribute_ = 0xffffffff;
	uint32_t collisionMask_ = 0xffffffff;
	Collider* collidedObject_ = nullptr;
	bool isGoal_ = false;
	std::list<Collider*> objects_;
	

protected:
	Vector3 rotationSpeed_;
	Vector3 spotVelocity_ = {0, 0, 0};
	float countSpotFlyingTimer_ = 0;

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
	/// <summary>
	/// 
	/// </summary>
	virtual void OnCollisionEnter();
	/// <summary>
	/// Get the collider
	/// </summary>
	/// <param name="collider"></param>
	void SetCollidedCollider(Collider* collider) { collidedObject_ = collider; };

	Collider* GetCollidedCollider() { return collidedObject_; };
	/// <summary>
	/// 
	/// </summary>
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
	/// <summary>
	/// Set the Parent of the collider
	/// </summary>
	/// <param name="parent"></param>
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
	/// <summary>
	/// Getter to show collider
	/// </summary>
	/// <returns></returns>
	bool GetShowCollider() { return showCollider_; };
	/// <summary>
	/// Setter to Set the collider
	/// </summary>
	/// <param name="set"></param>
	void SetShowCollider(bool set) { showCollider_ = set; };
	/// <summary>
	/// Set the collider color into red
	/// </summary>
	void TurnRED() { color_ = RED_; };
	/// <summary>
	/// Get attribute of the mask
	/// </summary>
	/// <returns></returns>
	uint32_t GetAttribute() { return collisionAttribute_; };
	/// <summary>
	/// Set the attribute
	/// </summary>
	/// <param name="attribute"></param>
	void SetAttribute(uint32_t attribute) { collisionAttribute_ = attribute; };
	/// <summary>
	/// Get the mask attribute
	/// </summary>
	/// <returns></returns>
	uint32_t GetMaskAttribute() { return collisionMask_; };
	/// <summary>
	/// Set the mask attribute
	/// </summary>
	/// <param name="attribute"></param>
	void SetMaskAttribute(uint32_t attribute) { collisionMask_ = attribute; };
	Vector3 GetRotationSpeed() { return rotationSpeed_; };
	void SetRotationSpeed(Vector3 speed) { rotationSpeed_ = speed; };
	void SetIsGoal(bool isGoal) { isGoal_ = isGoal; };
	bool GetIsGoal() { return isGoal_; };
	void SetObjects(std::list<Collider*> object) { objects_ = object; };
	std::list<Collider *> GetObjects() { return objects_; };
	virtual const WorldTransform& GetWorldTransform() = 0;
	virtual const char* GetName() = 0;
	virtual void SetVelocity(Vector3 velocity) = 0;
	void SetSpotVelocity(Vector3 velo) { spotVelocity_ = velo; };
	virtual ~Collider();
};
