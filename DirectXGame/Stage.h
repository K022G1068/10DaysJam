#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

enum ObjMode {
	onGrand,
	underGrand,
};

class Stage {
public:
	/// <summary>
	/// ステージの初期化
	/// </summary>
	/// <param name="num">1/4円の個数</param>
	void Initialize(int num, Vector3 Pos);
	void Update();
	float GetGrandPosY(Vector3 objPos);
	void Draw(ViewProjection& viewProjection);
	ObjMode GetMode(Vector3 objPos);
	~Stage();
	Vector3 Respown();
	float grav_ = 0.125f;
	Vector3 Sliding(Vector3 objPos);
	Vector3 GetSpotRot(Vector3 objPos);

private:
	int num_; // 扇の個数
	WorldTransform worldTransform_[4];
	Model* model_ = nullptr;
	float rad_ = 444.f;
	Vector3 correction = {.0f, .0f, 300.0f};
};
