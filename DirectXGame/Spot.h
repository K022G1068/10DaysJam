#pragma once
#include "Collider.h"
class Spot {
public:
	void Initialize();
	void Update();
	void Draw();
	void IncreaseRotationSpeed(Collider* collider);
};
