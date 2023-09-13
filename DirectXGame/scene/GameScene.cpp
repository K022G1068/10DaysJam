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
	delete spot1_;
	delete spot2_;
	delete spot3_;
	delete skydome_;
	delete stage_;
	delete gameManager_;

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
	modelSkydome_ = Model::CreateFromOBJ("Skydome", true);
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
	spot1_ = new Spot();
	spot2_ = new Spot();
	spot3_ = new Spot();
	skydome_ = new Skydome();
	stage_ = new Stage();
	gameManager_ = new GameManager();

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
	Vector3 goalPosition(0, -20.0f, 250.0f);
	Vector3 stagePosition(0, -30.0f, 300.0f);
	Vector3 spotPosition1(80.0f, -30.0f, 200.0f);
	Vector3 spotPosition2(-70.0f, -30.0f, 150.0f);
	Vector3 spotPosition3(-10.0f, -30.0f,-50.0f);
	player_->Initialize(modelPlayer_, playerPosition, viewProjection_, "Player");
	
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransform());
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	//enemy_->SetViewProjection(&followCamera_->GetViewProjection());
	player_->InitializeGauge(model_, modelGaugeBox_);
	spot1_->Initialize(modelSpot_, spotPosition1, viewProjection_);
	spot2_->Initialize(modelSpot_, spotPosition2, viewProjection_);
	spot3_->Initialize(modelSpot_, spotPosition3, viewProjection_);
	goal_->Initialize(modelGoal_, goalPosition, viewProjection_);
	stage_->Initialize(1, stagePosition);
	//enemy_->SetGoal(goalPosition);
	//enemy_->SetSpot(spotPosition);
	//enemy_->InitializeGauge(model_, modelGaugeBox_);
	player_->SetGoal(goalPosition);
	player_->SetGoal(goal_);
	player_->SetStage(stage_);
	spot1_->SetStage(stage_);
	spot2_->SetStage(stage_);
	spot3_->SetStage(stage_);
	objects_.push_back(player_);
	gameManager_->Initialize();
	gameManager_->GetGoal(goal_);
	//Initialize enemy
	for (int i = 0; i < MAX_ENEMY; i++) {
		Enemy* obj = new Enemy();
		obj->SetGameManager(gameManager_);
		obj->Initialize(modelEnemies_[i], enemiesPosition[i], viewProjection_, enemiesName[i]);
		obj->SetViewProjection(&followCamera_->GetViewProjection());
		obj->SetGoalPos(goalPosition);
		obj->SetSpot(spotPosition1);
		obj->SetSpot(spotPosition2);
		obj->SetSpot(spotPosition3);
		obj->SetGoal(goal_);
		obj->SetRandomNumber(i * 1000);
		obj->InitializeGauge(model_, modelGaugeBox_);
		obj->SetStage(stage_);
	
		obj->SetRandomRotationSpeed(i);
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
		enemy->GetSpotDistance();
	}
	//Texture
	skydome_->Initialize(modelSkydome_);

}

void GameScene::Update() {
	//enemy_->Update();
	player_->Update();
	goal_->Update();
	spot1_->Update();
	spot2_->Update();
	spot3_->Update();
	skydome_->Update();
	stage_->Update();
	gameManager_->Update();
	//Enemy update
	for (Enemy* enemy : enemies_) {
		if (enemy) {
			enemy->Update();
		}
	}

	//Remove enemy if goal
	{
		if (objects_.remove_if([](Collider* object) {
			if (object->GetIsGoal()) {
				return true;
			}
			return false;
			}))
		{
			for (Enemy* enemy : enemies_) {
				if (enemy) {

					enemy->SetObjects(objects_);
				}
			}
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
	
	CollisionManager::GetInstance()->Register(spot1_);
	CollisionManager::GetInstance()->Register(spot2_);
	CollisionManager::GetInstance()->Register(spot3_);
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
	spot1_->Draw(viewProjection_);
	spot2_->Draw(viewProjection_);
	spot3_->Draw(viewProjection_);
	stage_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);

	for (Enemy* enemy : enemies_) {
		enemy->DrawPrimitive();
	}
	
	player_->DrawPrimitive();
	goal_->DrawPrimitive();
	spot1_->DrawPrimitive();
	spot2_->DrawPrimitive();
	spot3_->DrawPrimitive();
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
