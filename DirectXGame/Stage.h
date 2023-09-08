#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"
class Stage {
public:
	void Initialize();
	void Update();
	float GetGrandPosY(Vector3 objPos);
	void Draw(ViewProjection &viewProjection);
	~Stage();

private:
	float theta_;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};