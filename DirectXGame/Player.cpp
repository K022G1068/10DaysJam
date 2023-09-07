#include "Player.h"

void Player::Initialize(
    Model* model, Vector3& playerPosition, ViewProjection& viewProjection, const char* name) {
	assert(model);
	//textureHandle_ = textureHandle;
	name_ = name;
	BaseInit(viewProjection, showCollider_, name_);
	worldTransform_.Initialize();
	worldTransform_.translation_ = playerPosition;
	model_ = model;
	input_ = Input::GetInstance();
}

Player::~Player() {}

void Player::Update() { 
	OnUpdate();
	Move();
	SetColliderPosition();
	SetCollider(
	    colliderPos_,
	    radius_);
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
	colliderPos_.y = worldTransform_.translation_.y + radius_;
	colliderPos_.z = worldTransform_.translation_.z;
}

void Player::Move() {
	Vector3 degree = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_A)) {
		degree.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_D)) {
		degree.x += kCharacterSpeed;
	}

	if (input_->PushKey(DIK_SPACE)) {
		// move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_LSHIFT)) {
		degree.y -= kCharacterSpeed;
	}

	if (input_->PushKey(DIK_S)) {
		degree.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_W)) {
		degree.y += kCharacterSpeed;
	}

	const float kRotSpeed = 0.02f;
	if (input_->PushKey(DIK_Q)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_E)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}

	worldTransform_.translation_.x += degree.x;
	worldTransform_.translation_.y += degree.y;
	worldTransform_.translation_.z += degree.z;
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
	//DrawCollider();
}
