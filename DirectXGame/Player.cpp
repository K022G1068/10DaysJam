#include "Player.h"
//#include "PlayerCamera.h"

void Player::Initialize(
    Model* model, Vector3& playerPosition, ViewProjection& viewProjection,
    const char* name) {
	assert(model);
	//textureHandle_ = textureHandle;
	name_ = name;
	BaseInit(viewProjection, showCollider_, name_);
	worldTransform_.Initialize();
	worldTransform_.translation_ = playerPosition;
	worldTransform_.scale_ = {1.4f, 1.4f, 1.4f};
	model_ = model;
	input_ = Input::GetInstance();

	//Collider
	Vector3 colliderPos(0, 5.0f, 0.0f);
	Collider::BaseInit(viewProjection, showCollider_, name_);
	Collider::SetCollider(colliderPos, radius_);
	Collider::SetColliderParent(&worldTransform_);

	//Dash
	dash_ = new Dash();
	dash_->Initialize(rotationSpeed_);

	//Easing
	easing_.time = 0;
	easing_.startPos = {0,0,0};
	easing_.duration = 20.0f;
	easing_.change = 10;
}

void Player::InitializeGauge(Model* gaugeModel, Model* gaugeModelBox) {
	// Gauge
	gauge_ = new Gauge();
	Vector3 gaugePos_(0.0f, 15.0f, 0.0f);
	gauge_->Initialize(gaugeModel, gaugeModelBox,gaugePos_, viewProjection_, radius_);
	
}

Player::~Player() {}

void Player::Update() {
	Move();
	worldTransform_.rotation_ += rotationSpeed_;

	//Gauge
	gauge_->GetCameraRotation(viewProjection_->rotation_.y);
	gauge_->SetPosition(worldTransform_.translation_);
	gauge_->GetRotation(rotationSpeed_);
	gauge_->Update();



	Collider::OnUpdate();

	//ImGui
	ImGui::DragFloat3("Rotation", &rotationSpeed_.x, 0.001f);

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

void Player::OnCollision() { ImGui::Text("HOOOOTTTTTTT"); }

void Player::SetColliderPosition() {
	colliderPos_.x = worldTransform_.translation_.x;
	colliderPos_.y = worldTransform_.translation_.y + radius_;
	colliderPos_.z = worldTransform_.translation_.z;
}

void Player::Move() {

	if (Input::GetInstance()->GetJoystickState(0, joyState_)) {
		if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState_))
		{
			Vector3 move = {0, 0, 0};

			const float kCharacterSpeed = 0.5f;
			if (easing_.time <= easing_.duration) {
				easing_.time += 0.01f;
			}

			move = {
			    (float)joyState_.Gamepad.sThumbLX / SHRT_MAX, 0.1f,
			    (float)joyState_.Gamepad.sThumbLY / SHRT_MAX
			};
			
			move = Normalize(move) * kCharacterSpeed;
			move.y = 0.0f;

			Matrix4x4 rotmat = MakeRotationMatrixY(viewProjection_->rotation_.y);
			move = TransformNormal(move, rotmat);

			if ((joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) && !(prevjoyState_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) && dash_->GetCanDash()) {
				ImGui::Text("DASSSHHHH" );
				dash_->ActivateDash();
			} 
			else {
				dash_->DisactivateDash(easing_);
			}

			if (dash_->GetDash())
			{
				move *= dash_->EaseInQuad(easing_) * 5.0f;
				move.y = 0.0f;
			}


			worldTransform_.translation_ += move;
		}
		
	} else {
		ImGui::Text("No controller detected");
	}
	
	
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
	gauge_->Draw(viewProjection);
}

void Player::DrawPrimitive() { 
	//gauge_->DrawBox();
	Collider::DrawCollider();
}
