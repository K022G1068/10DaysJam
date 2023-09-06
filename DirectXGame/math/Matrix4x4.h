#pragma once
#include "Vector3.h"
#include <math.h>
/// <summary>
/// 4x4行列
/// </summary>
struct Matrix4x4 final {
	float m[4][4];
};
Matrix4x4& operator*=(Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 MakeScaleMatrix(const Vector3& scale);
Matrix4x4 MakeRotationMatrixX(const float& theta);
Matrix4x4 MakeRotationMatrixY(const float& theta);
Matrix4x4 MakeRotationMatrixZ(const float& theta);
Matrix4x4 MakeTransformMatrix(const Vector3& trans);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);
