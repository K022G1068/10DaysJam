#include "Dash.h"

void Dash::Initialize(Vector3 rotationSpeed) { rotationSpeed_ = rotationSpeed; }

void Dash::DisactivateDash(Easing& e) {
	dashing_ = false;
	e.time = 0;
	e.startPos = {0, 0, 0};
	e.duration = 0.2f;
	e.change = 50.0f;
}


Vector3 Dash::easeOutQuint(Easing e) {
	Vector3 dashPos;
	e.time /= e.duration;
	dashPos.x = e.change - powf(e.change - e.time, 5.0f) + e.startPos.x;
	dashPos.y = e.change - powf(e.change - e.time, 5.0f) + e.startPos.y;
	dashPos.z = e.change - powf(e.change - e.time, 5.0f) + e.startPos.z;
	return dashPos; 
}

Vector3 Dash::EaseInQuad(Easing e) {
	Vector3 dashPos;
	e.time /= e.duration;
	dashPos.x = e.change * e.time * e.time + e.startPos.x;
	dashPos.y = e.change * e.time * e.time + e.startPos.y;
	dashPos.z = e.change * e.time * e.time + e.startPos.z;
	return dashPos;
}