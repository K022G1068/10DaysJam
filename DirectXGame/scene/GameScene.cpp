#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete player_;
	delete enemy_;
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

	//Instances
	player_ = new Player();
	enemy_ = new Enemy();

	//Initialize
	Vector3 playerPosition(0, -5.0f, 10.0f);
	Vector3 enemyPosition(2.0f, -5.0f, 10.0f);
	player_->Initialize(modelPlayer_, playerPosition, viewProjection_, "Player");
	enemy_->Initialize(modelPlayer_, enemyPosition, viewProjection_, "Enemy1");
}

void GameScene::Update() 
{ 
	enemy_->Update();
	player_->Update(); 

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
	enemy_->DrawCollider();
	player_->DrawCollider();
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
