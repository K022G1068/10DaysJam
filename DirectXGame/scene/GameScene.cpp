#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete player_;
	delete model_;
	delete followCamera_;
	delete modelGaugeBox_;
	delete modelPlayer_;
	delete goal_;
	delete spot_;

	for (Enemy* enemy : enemies_) {
		delete enemy;
		enemy = nullptr;
	}
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
	modelGaugeBox_ = Model::CreateFromOBJ("Gage", true);
	modelGoal_ = Model::CreateFromOBJ("Goal", true);
	modelSpot_ = Model::CreateFromOBJ("Speedupspot", true);
	modelEnemy1_ = Model::CreateFromOBJ("Enemy1", true);
	modelEnemy2_ = Model::CreateFromOBJ("Enemy2", true);
	modelEnemy3_ = Model::CreateFromOBJ("Enemy3", true);
	modelEnemy4_ = Model::CreateFromOBJ("Enemy4", true);
	modelEnemy5_ = Model::CreateFromOBJ("Enemy5", true);
	modelEnemy6_ = Model::CreateFromOBJ("Enemy6", true);
	modelEnemies_.push_back(modelEnemy1_);
	modelEnemies_.push_back(modelEnemy2_);
	modelEnemies_.push_back(modelEnemy3_);
	modelEnemies_.push_back(modelEnemy4_);
	modelEnemies_.push_back(modelEnemy5_);
	modelEnemies_.push_back(modelEnemy6_);
	model_ = Model::Create();
	
	//Instances
	player_ = new Player();
	//enemy_ = new Enemy();
	followCamera_ = new FollowCamera();
	goal_ = new Goal();
	spot_ = new Spot();

	//Initialize
	Vector3 playerPosition(0, -30.0f, 100.0f);
	Vector3 enemiesPosition[6] = {
	    {30.0f,  -30.0f, 20.0f},
        {90.0f,  -30.0f, 20.0f},
        {0.0f,   -30.0f, 20.0f},
	    {-30.0f, -30.0f, 20.0f},
        {-60.0f, -30.0f, 20.0f},
        {60.0f,  -30.0f, 20.0f}
    };
	
	const char* enemiesName[6] = {
	   "Enemy1", "Enemy2", "Enemy3", "Enemy4", "Enemy5", "Enemy6",
	};

	Vector3 railPosition(0, 0, 0.0f);
	Vector3 goalPosition(0, -30.0f, 300.0f);
	Vector3 spotPosition(50.0f, -30.0f, 250.0f);
	player_->Initialize(modelPlayer_, playerPosition, viewProjection_, "Player");
	
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransform());
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	//enemy_->SetViewProjection(&followCamera_->GetViewProjection());
	player_->InitializeGauge(model_, modelGaugeBox_);
	spot_->Initialize(modelSpot_, spotPosition, viewProjection_);
	goal_->Initialize(modelGoal_, goalPosition, viewProjection_);
	//enemy_->SetGoal(goalPosition);
	//enemy_->SetSpot(spotPosition);
	//enemy_->InitializeGauge(model_, modelGaugeBox_);
	player_->SetGoal(goalPosition);
	objects_.push_back(player_);
	//Initialize enemy
	for (int i = 0; i < MAX_ENEMY; i++) {
		Enemy* obj = new Enemy();
		obj->Initialize(modelEnemies_[i], enemiesPosition[i], viewProjection_, enemiesName[i]);
		obj->SetViewProjection(&followCamera_->GetViewProjection());
		obj->SetGoal(goalPosition);
		obj->SetSpot(spotPosition);
		obj->SetRandomNumber(i * 1000);
		obj->InitializeGauge(model_, modelGaugeBox_);
		obj->GetRandomRotation(i);
		enemies_.push_back(obj);
		objects_.push_back(obj);
	}
	//enemies_.push_back(player_)
	for (Enemy* enemy : enemies_) {
		enemy->SetObjects(objects_);
		enemy->SetPlayer(player_);
	}
	for (Enemy* enemy : enemies_) {
		enemy->GetEnemyDistance();
	}
	//Texture
	
}

void GameScene::Update() {
	//enemy_->Update();
	player_->Update();
	goal_->Update();
	spot_->Update();

	//Enemy update
	for (Enemy* enemy : enemies_) {
		if (enemy) {
			enemy->Update();
			enemy->SetPlayer(player_);
		}
	}

	// Follow camera
	followCamera_->Update();
	viewProjection_.matView = followCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
	viewProjection_.TransferMatrix();

	// Collision
	CollisionManager::GetInstance()->Register(player_);
	CollisionManager::GetInstance()->Register(goal_);
	for (Enemy* enemy : enemies_) {
		CollisionManager::GetInstance()->Register(enemy);
	}
	
	CollisionManager::GetInstance()->Register(spot_);
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
	for (Enemy* enemy : enemies_) {
		enemy->Draw(viewProjection_);
	}
	player_->Draw(viewProjection_);
	goal_->Draw(viewProjection_);
	spot_->Draw(viewProjection_);

	for (Enemy* enemy : enemies_) {
		enemy->DrawPrimitive();
	}
	
	player_->DrawPrimitive();
	goal_->DrawPrimitive();
	spot_->DrawPrimitive();
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
