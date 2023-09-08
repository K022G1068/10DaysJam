#pragma once
#define MAX_ROTATION 0.3f
#define MIN_ROTATION 0.06f
#include "Vector3.h"
#include "MathUtility.h"

class Dash {
public:
	void Initialize(Vector3 rotationSpeed);
	void ActivateDash();
	Vector3 easeOutQuint(Vector3 pos);

private:
	bool canDash_;
	Vector3 rotationSpeed_;
	float rotationPercentage_;


};
