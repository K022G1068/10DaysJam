#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

enum ObjMode {
	onGrand,
	Goal,
	underGrand,
};

class Stage {
public:
	void Initialize();
	void Update();
	float GetGrandPosY(Vector3 objPos);
	void Draw(ViewProjection& viewProjection);
	ObjMode GetMode(Vector3 objPos);
	~Stage();

	float grav_ = 1.f;
private:
	float theta_;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	float rad_ = 10.f;
};