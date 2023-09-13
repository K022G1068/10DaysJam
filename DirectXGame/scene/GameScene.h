#pragma once
#define MAX_ENEMY 6
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
#include "Goal.h"
#include "Spot.h"
#include "Skydome.h"
#include <vector>
#include "Stage.h"
#include "GameManager.h"

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

	void Delete();

	void Reset();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	
	Sprite* sprite_ = nullptr;
	Sprite* titleScene_ = nullptr;
	Sprite* winSprite_ = nullptr;
	Sprite* loseSprite_ = nullptr;
	
	
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	bool isDebugCameraActive_ = false;

	//Instances
	Player* player_ = nullptr;
	std::vector<Enemy*> enemies_;
	std::list<Collider*> objects_;
	//Enemy* enemy_ = nullptr;
	FollowCamera* followCamera_ = nullptr;
	Goal* goal_ = nullptr;
	Spot* spot1_ = nullptr;
	Spot* spot2_ = nullptr;
	Spot* spot3_ = nullptr;
	Spot* spot4_ = nullptr;
	Spot* spot5_ = nullptr;
	Spot* spot6_ = nullptr;
	Spot* spot7_ = nullptr;
	Spot* spot8_ = nullptr;
	Skydome* skydome_ = nullptr;
	Stage* stage_ = nullptr;
	GameManager* gameManager_ = nullptr;

	//Model
	Model* model_ = nullptr;
	Model* modelSkydome_ = nullptr;
	Model* modelPlayer_ = nullptr;
	Model* modelGaugeBox_ = nullptr;
	Model* modelGoal_ = nullptr;
	Model* modelSpot_ = nullptr;
	std::vector<Model*> modelEnemies_;
	Model* modelEnemy1_ = nullptr;
	Model* modelEnemy2_ = nullptr;
	Model* modelEnemy3_ = nullptr;
	Model* modelEnemy4_ = nullptr;
	Model* modelEnemy5_ = nullptr;
	Model* modelEnemy6_ = nullptr;

	//Texture
	uint32_t textureHandle_ = 0;
	uint32_t titleTextureHandle_ = 0;
	uint32_t winTexture_ = 0;
	uint32_t loseTexture_ = 0;
	
};
