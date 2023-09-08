#pragma once

#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MathUtility.h"
#include <Input.h>

class Cam {
public:
	void Initialize(Input* input);
	void Update();
	WorldTransform& GetWorldTransform() { return worldTransform_; }
	ViewProjection& GetViewProjection() { return viewProjection_; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Input* input_;
};
