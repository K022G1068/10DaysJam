#pragma once

#include "Audio.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "Cam.h"
#include "Stage.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	uint32_t textureHandle_ = 0;
	uint32_t titleTextureHandle_ = 0;
	Sprite* sprite_ = nullptr;
	Sprite* titleScene_ = nullptr;

	// Skydome* skydome_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	bool isDebugCameraActive_ = false;

	// Instances
	Player* player_ = nullptr;
	Enemy* enemy_ = nullptr;
	Stage* stage_ = nullptr;

	// Model
	Model* model_ = nullptr;
	Model* modelSkydome_ = nullptr;
	Model* modelPlayer_ = nullptr;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	bool p = false;
	Cam* cam_;
};
