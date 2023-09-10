#pragma once
#define MAX_ROTATION 0.3f
#define MIN_ROTATION 0.06f
#include "Vector3.h"
#include "MathUtility.h"

struct Easing {
	float time;
	Vector3 startPos;
	float change;
	float duration;
};
class Dash {
public:
	void Initialize(Vector3 rotationSpeed);
	void ActivateDash() { dashing_ = true; };
	void DisactivateDash(Easing& e);
	bool GetDash() { return dashing_; };
	bool GetCanDash() { return canDash_; };
	void SetCanDash(bool candash) { canDash_ = candash; };
	Vector3 easeOutQuint(Easing e);
	Vector3 EaseInQuad(Easing e);

private:
	bool canDash_ = true;
	bool dashing_ = false;
	Vector3 rotationSpeed_;
	float rotationPercentage_;
	Easing easing_;
	


};
