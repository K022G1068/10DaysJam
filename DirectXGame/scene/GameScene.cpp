#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete player_;
	delete enemy_;
	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	//Read
	modelPlayer_ = Model::CreateFromOBJ("Player", true);
	model_ = Model::Create();
	
	//Instances
	playerCamera_ = new PlayerCamera();
	player_ = new Player();
	enemy_ = new Enemy();

	//Initialize
	Vector3 playerPosition(0, -30.0f, 100.0f);
	Vector3 enemyPosition(30.0f, -20.0f, 20.0f);
	Vector3 railPosition(0, 0, 0.0f);
	enemy_->Initialize(modelPlayer_, model_, enemyPosition, viewProjection_, "Enemy1");
	playerCamera_->Initialize(railPosition, {0, 0, 0});
	player_->Initialize(modelPlayer_, model_, playerPosition, viewProjection_, "Player");
	player_->SetParent(&playerCamera_->GetWorldTransform());
	player_->SetPlayerCamera(playerCamera_);
	//Texture
	
}

void GameScene::Update() 
{ 
	enemy_->Update();
	player_->Update();

	//Camera update
	playerCamera_->Update();
	viewProjection_.matView = playerCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = playerCamera_->GetViewProjection().matProjection;
	viewProjection_.TransferMatrix();

	CollisionManager::GetInstance()->Register(player_);
	CollisionManager::GetInstance()->Register(enemy_);
	CollisionManager::GetInstance()->CheckAllCollisions();
	CollisionManager::GetInstance()->ClearList();
}



void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	
	enemy_->Draw(viewProjection_);
	player_->Draw(viewProjection_);
	enemy_->DrawPrimitive();
	player_->DrawPrimitive();
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
