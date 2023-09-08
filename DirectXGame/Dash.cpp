#include "Dash.h"

void Dash::Initialize(Vector3 rotationSpeed) { rotationSpeed_ = rotationSpeed; }


Vector3 Dash::easeOutQuint(Vector3 pos) {
	Vector3 dashPos;
	dashPos.x = 1 - powf(1 - pos.x, 5.0f);
	dashPos.y = 1 - powf(1 - pos.y, 5.0f);
	dashPos.z = 1 - powf(1 - pos.z, 5.0f);
	return dashPos; 
}
