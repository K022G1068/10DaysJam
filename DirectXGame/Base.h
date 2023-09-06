#pragma once
#include "Vector3.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"
#include "ImGuiManager.h"
#include "MathUtility.h"
#include "Collider.h"
class Base : Collider {
public:
	/// <summary>
	/// Initialize
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// Update
	/// </summary>
	virtual void Update();
	/// <summary>
	/// Move function
	/// </summary>
	virtual void Move();
	/// <summary>
	/// Collision callback
	/// </summary>
	virtual void OnCollision() override;
	/// <summary>
	/// Get the world position of the object
	/// </summary>
	/// <returns></returns>
	virtual Vector3 GetWorldPosition() override;
	/// <summary>
	/// Draw function
	/// </summary>
	virtual void Draw();
};
