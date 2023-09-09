#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Enemy.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "FollowCamera.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene{

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
	
	Sprite* sprite_ = nullptr;
	Sprite* titleScene_ = nullptr;
	
	//Skydome* skydome_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	bool isDebugCameraActive_ = false;

	//Instances
	Player* player_ = nullptr;
	Enemy* enemy_ = nullptr;
	FollowCamera* followCamera_ = nullptr;

	//Model
	Model* model_ = nullptr;
	Model* modelSkydome_ = nullptr;
	Model* modelPlayer_ = nullptr;
	Model* modelGaugeBox_ = nullptr;

	//Texture
	uint32_t textureHandle_ = 0;
	uint32_t titleTextureHandle_ = 0;
	
};
