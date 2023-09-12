#include "Player.h"

void Player::Initialize(
    Stage* stage, Model* model, Vector3& playerPosition, ViewProjection& viewProjection,
    const char* name) {
	assert(model);
	// textureHandle_ = textureHandle;
	name_ = name;
	BaseInit(viewProjection, showCollider_, name_);
	worldTransform_.Initialize();
	worldTransform_.translation_ = playerPosition;
	model_ = model;
	input_ = Input::GetInstance();
	stage_ = stage;
}

Player::~Player() {}

void Player::Update() {
	OnUpdate();
	SetColliderPosition();
	SetCollider(colliderPos_, radius_);
	if (stage_->GetMode(worldTransform_.translation_) != underGrand) {
		worldTransform_.translation_.y = stage_->GetGrandPosY(worldTransform_.translation_);
		Move();
	}
	if (stage_->GetMode(worldTransform_.translation_) == underGrand) {
		moveSpd_.y += stage_->grav_;
		worldTransform_.translation_.y -= moveSpd_.y;
	}
	if (worldTransform_.translation_.y < -10)
		worldTransform_.translation_ = {.0f, .0f, .0f};
	ImGui::Begin("playerPos");
	ImGui::Text("");
	ImGui::Text(
	    "x %f, y %f, z %f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z);
	ImGui::End();

	worldTransform_.UpdateMatrix();
}

Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

void Player::OnCollision() { ImGui::Text("HIOTTTTTTT"); }

void Player::SetColliderPosition() {
	colliderPos_.x = worldTransform_.translation_.x;
	colliderPos_.y = worldTransform_.translation_.y + 5.0f;
	colliderPos_.z = worldTransform_.translation_.z;
}

void Player::Move() {
	Vector3 move = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_A)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_D)) {
		move.x += kCharacterSpeed;
	}

	if (input_->PushKey(DIK_S)) {
		move.z -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_W)) {
		move.z += kCharacterSpeed;
	}

	const float kRotSpeed = 0.02f;
	if (input_->PushKey(DIK_Q)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_E)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
	// DrawCollider();
}
