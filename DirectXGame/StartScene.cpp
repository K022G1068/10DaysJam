#include "StartScene.h"

void StartScene::Initialize(uint32_t titleTextureHandle)
{
	titleSprite_ = Sprite::Create(titleTextureHandle, {0, 0});
}

void StartScene::Update() {}

void StartScene::Draw() 
{
	titleSprite_->Draw();

}
