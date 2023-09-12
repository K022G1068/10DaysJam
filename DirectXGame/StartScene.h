#pragma once
#include <Sprite.h>

class StartScene 
{
public:

	void Initialize(uint32_t titleTextureHandle);

	void Update();

	void Draw();

private:
	Sprite* titleSprite_ = nullptr;
	uint32_t titleTextureHandle_ = 0u;


};
