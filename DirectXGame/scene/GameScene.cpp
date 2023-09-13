#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

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
	delete spot4_;
	delete spot5_;
	delete spot6_;
	delete spot7_;
	delete spot8_;
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

	// Read
	winTexture_ = TextureManager::Load("winorlose/Win.png");
	loseTexture_ = TextureManager::Load("winorlose/Lose.png");


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


	//Texture
	winSprite_ = Sprite::Create(winTexture_, {0, 0});
	loseSprite_ = Sprite::Create(loseTexture_, {0, 0});

	// Instances
	player_ = new Player();
	// enemy_ = new Enemy();
	followCamera_ = new FollowCamera();
	goal_ = new Goal();
	spot1_ = new Spot();
	spot2_ = new Spot();
	spot3_ = new Spot();
	spot4_ = new Spot();
	spot5_ = new Spot();
	spot6_ = new Spot();
	spot7_ = new Spot();
	spot8_ = new Spot();
	skydome_ = new Skydome();
	stage_ = new Stage();
	gameManager_ = new GameManager();

	// Initialize
	Vector3 playerPosition(0, -30.0f, 10.0f);
	Vector3 enemiesPosition[6] = {
	    {50.0f,  -30.0f, 160.0f + -40.0f},
        {60.0f,  -30.0f, 120.0f + -40.0f},
        {70.0f,   -30.0f, 80.0f + -40.0f},
	    {-50.0f, -30.0f, 160.0f + -40.0f},
        {-60.0f, -30.0f, 120.0f + -40.0f},
        {-70.0f,  -30.0f, 80.0f + -40.0f}
    };

	const char* enemiesName[6] = {
	    "Enemy1", "Enemy2", "Enemy3", "Enemy4", "Enemy5", "Enemy6",
	};

	Vector3 railPosition(0, 0, 0.0f);
	Vector3 goalPosition(0, -25.0f, 280.0f);
	Vector3 stagePosition(0, -30.0f, 300.0f);
	Vector3 spotPosition1(0.0f, -15.0f, 175.0f);
	Vector3 spotPosition2(0.0f, -15.0f, 220.0f);
	Vector3 spotPosition3(0.0f, -15.0f, 60.0f);
	Vector3 spotPosition4(-200.0f, -15.0f, 0.0f);
	Vector3 spotPosition5(200.0f, -15.0f, 0.0f);
	Vector3 spotPosition6(-45.0f, -15.0f, 225.0f);
	Vector3 spotPosition7(45.0f, -15.0f, 215.0f);
	Vector3 spotPosition8(0.0f, -15.0f, 260.0f);
	player_->Initialize(modelPlayer_, playerPosition, viewProjection_, "Player");

	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransform());
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	// enemy_->SetViewProjection(&followCamera_->GetViewProjection());
	player_->InitializeGauge(model_, modelGaugeBox_);
	spot1_->Initialize(modelSpot_, spotPosition1, viewProjection_);
	spot2_->Initialize(modelSpot_, spotPosition2, viewProjection_);
	spot3_->Initialize(modelSpot_, spotPosition3, viewProjection_);
	spot4_->Initialize(modelSpot_, spotPosition4, viewProjection_);
	spot5_->Initialize(modelSpot_, spotPosition5, viewProjection_);
	spot6_->Initialize(modelSpot_, spotPosition6, viewProjection_);
	spot7_->Initialize(modelSpot_, spotPosition7, viewProjection_);
	spot8_->Initialize(modelSpot_, spotPosition8, viewProjection_);
	goal_->Initialize(modelGoal_, goalPosition, viewProjection_);
	stage_->Initialize(1, stagePosition);
	// enemy_->SetGoal(goalPosition);
	// enemy_->SetSpot(spotPosition);
	// enemy_->InitializeGauge(model_, modelGaugeBox_);
	player_->SetGoal(goalPosition);
	player_->SetGoal(goal_);
	player_->SetStage(stage_);
	spot1_->SetStage(stage_);
	spot2_->SetStage(stage_);
	spot3_->SetStage(stage_);
	spot4_->SetStage(stage_);
	spot5_->SetStage(stage_);
	spot6_->SetStage(stage_);
	spot7_->SetStage(stage_);
	spot8_->SetStage(stage_);
	objects_.push_back(player_);
	gameManager_->Initialize();
	gameManager_->GetGoal(goal_);
	player_->SetGameManager(gameManager_);
	// Initialize enemy
	for (int i = 0; i < MAX_ENEMY; i++) {
		Enemy* obj = new Enemy();
		obj->SetGameManager(gameManager_);
		obj->Initialize(modelEnemies_[i], enemiesPosition[i], viewProjection_, enemiesName[i]);
		obj->SetViewProjection(&followCamera_->GetViewProjection());
		obj->SetGoalPos(goalPosition);
		obj->SetSpot(spotPosition1);
		obj->SetSpot(spotPosition2);
		obj->SetSpot(spotPosition3);
		obj->SetSpot(spotPosition4);
		obj->SetSpot(spotPosition5);
		obj->SetSpot(spotPosition6);
		obj->SetSpot(spotPosition7);
		obj->SetSpot(spotPosition8);
		obj->SetGoal(goal_);
		obj->SetRandomNumber(i * 1000);
		obj->InitializeGauge(model_, modelGaugeBox_);
		obj->SetStage(stage_);

		obj->SetRandomRotationSpeed(i);
		enemies_.push_back(obj);
		objects_.push_back(obj);
	}
	// enemies_.push_back(player_)
	for (Enemy* enemy : enemies_) {
		enemy->SetObjects(objects_);
		enemy->SetPlayer(player_);
	}
	for (Enemy* enemy : enemies_) {
		enemy->GetEnemyDistance();
		enemy->GetSpotDistance();
	}
	// Texture
	skydome_->Initialize(modelSkydome_);
}

void GameScene::Update() {

	if (!gameManager_->GetIsover())
	{
		// enemy_->Update();
		player_->Update();
		goal_->Update();
		spot1_->Update();
		spot2_->Update();
		spot3_->Update();
		spot4_->Update();
		spot5_->Update();
		spot6_->Update();
		spot7_->Update();
		spot8_->Update();
		skydome_->Update();
		stage_->Update();
		gameManager_->Update();
		// Enemy update
		for (Enemy* enemy : enemies_) {
			if (enemy) {
				enemy->Update();
			}
		}

		// Remove enemy if goal
		{
			if (objects_.remove_if([](Collider* object) {
				    if (object->GetIsGoal()) {
					    return true;
				    }
				    return false;
			    })) {
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
		CollisionManager::GetInstance()->Register(spot4_);
		CollisionManager::GetInstance()->Register(spot5_);
		CollisionManager::GetInstance()->Register(spot6_);
		CollisionManager::GetInstance()->Register(spot7_);
		CollisionManager::GetInstance()->Register(spot8_);
		CollisionManager::GetInstance()->CheckAllCollisions();
		CollisionManager::GetInstance()->ClearList();
	}
	else
	{
		if (gameManager_->GetWinBool())
		{
			
		} else if (gameManager_->GetLoseBool())
		{
			if (input_->PushKey(DIK_SPACE))
			{
				Reset();
			}
		}
		
		//Reset();
	}
	
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
	spot4_->Draw(viewProjection_);
	spot5_->Draw(viewProjection_);
	spot6_->Draw(viewProjection_);
	spot7_->Draw(viewProjection_);
	spot8_->Draw(viewProjection_);
	stage_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);

	//for (Enemy* enemy : enemies_) {
	//	enemy->DrawPrimitive();
	//}

	//player_->DrawPrimitive();
	//goal_->DrawPrimitive();
	//spot1_->DrawPrimitive();
	//spot2_->DrawPrimitive();
	//spot3_->DrawPrimitive();
	//spot4_->DrawPrimitive();
	//spot5_->DrawPrimitive();
	//spot6_->DrawPrimitive();
	//spot7_->DrawPrimitive();
	//spot8_->DrawPrimitive();
	
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	
	if (gameManager_->GetIsover())
	{
		if (gameManager_->GetWinBool()) {
			winSprite_->Draw();
		} else if (gameManager_->GetLoseBool()) {
			loseSprite_->Draw();
		}
	}
	else
	{
		gameManager_->Draw();
	}
	//  スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Delete() {
	delete player_;
	delete model_;
	delete followCamera_;
	delete modelGaugeBox_;
	delete modelPlayer_;
	delete goal_;
	delete spot1_;
	delete spot2_;
	delete spot3_;
	delete spot4_;
	delete spot5_;
	delete spot6_;
	delete spot7_;
	delete spot8_;
	delete skydome_;
	delete stage_;
	delete gameManager_;

	for (Enemy* enemy : enemies_) {
		delete enemy;
		enemy = nullptr;
	}
}

void GameScene::Reset() { 
	Vector3 enemiesPosition[6] = {
	    {50.0f,  -30.0f, 160.0f + -40.0f},
        {60.0f,  -30.0f, 120.0f + -40.0f},
	    {70.0f,  -30.0f, 80.0f + -40.0f },
        {-50.0f, -30.0f, 160.0f + -40.0f},
	    {-60.0f, -30.0f, 120.0f + -40.0f},
        {-70.0f, -30.0f, 80.0f + -40.0f }
    };
	objects_.clear();
	goal_->Reset();

	for (int i = 0; i < MAX_ENEMY; i++) {
		enemies_[i]->ResetPosition(enemiesPosition[i]);
		enemies_[i]->Reset(i);
		objects_.push_back(enemies_[i]);
	}
	player_->Reset();
	objects_.push_back(player_);
	gameManager_->Restart();
	
}
