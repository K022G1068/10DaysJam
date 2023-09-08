#include "MathUtility.h"
#include <math.h>

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{
	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2],
	};

	return result;
}

Matrix4x4 Inverse(const Matrix4x4& matrix) {
	Matrix4x4 result;
	float determinant = matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] +
	                    matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1] +
	                    matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2] -
	                    matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1] -
	                    matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3] -
	                    matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2] -
	                    matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] -
	                    matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1] -
	                    matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] +
	                    matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1] +
	                    matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] +
	                    matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2] +
	                    matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3] +
	                    matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1] +
	                    matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2] -
	                    matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1] -
	                    matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3] -
	                    matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2] -
	                    matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0] -
	                    matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0] -
	                    matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0] +
	                    matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0] +
	                    matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0] +
	                    matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0];

	float determinantRecp = 1.0f / determinant;

	result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] +
	                  matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1] +
	                  matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2] -
	                  matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1] -
	                  matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3] -
	                  matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2]) *
	                 determinantRecp;
	result.m[0][1] = (-matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][3] -
	                  matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][1] -
	                  matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][2] +
	                  matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][1] +
	                  matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][3] +
	                  matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][2]) *
	                 determinantRecp;
	result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][3] +
	                  matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][1] +
	                  matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][2] -
	                  matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][1] -
	                  matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][3] -
	                  matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][2]) *
	                 determinantRecp;
	result.m[0][3] = (-matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] -
	                  matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1] -
	                  matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2] +
	                  matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1] +
	                  matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3] +
	                  matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2]) *
	                 determinantRecp;
	result.m[1][0] = (-matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] -
	                  matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0] -
	                  matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2] +
	                  matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0] +
	                  matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3] +
	                  matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2]) *
	                 determinantRecp;
	result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][3] +
	                  matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][0] +
	                  matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][2] -
	                  matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][0] -
	                  matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][3] -
	                  matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][2]) *
	                 determinantRecp;
	result.m[1][2] = (-matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][3] -
	                  matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][0] -
	                  matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][2] +
	                  matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][0] +
	                  matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][3] +
	                  matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][2]) *
	                 determinantRecp;
	result.m[1][3] = (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] +
	                  matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0] +
	                  matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2] -
	                  matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0] -
	                  matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3] -
	                  matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2]) *
	                 determinantRecp;
	result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] +
	                  matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0] +
	                  matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1] -
	                  matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0] -
	                  matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3] -
	                  matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1]) *
	                 determinantRecp;
	result.m[2][1] = (-matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][3] -
	                  matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][0] -
	                  matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][1] +
	                  matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][0] +
	                  matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][3] +
	                  matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][1]) *
	                 determinantRecp;
	result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][3] +
	                  matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][0] +
	                  matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][1] -
	                  matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][0] -
	                  matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][3] -
	                  matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][1]) *
	                 determinantRecp;
	result.m[2][3] = (-matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] -
	                  matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0] -
	                  matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1] +
	                  matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0] +
	                  matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3] +
	                  matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1]) *
	                 determinantRecp;
	result.m[3][0] = (-matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] -
	                  matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0] -
	                  matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1] +
	                  matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0] +
	                  matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2] +
	                  matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1]) *
	                 determinantRecp;
	result.m[3][1] = (matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][2] +
	                  matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][0] +
	                  matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][1] -
	                  matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][0] -
	                  matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][2] -
	                  matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][1]) *
	                 determinantRecp;
	result.m[3][2] = (-matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][2] -
	                  matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][0] -
	                  matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][1] +
	                  matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][0] +
	                  matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][2] +
	                  matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][1]) *
	                 determinantRecp;
	result.m[3][3] = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
	                  matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
	                  matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -
	                  matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
	                  matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] -
	                  matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]) *
	                 determinantRecp;
	return result;
}

float Lerp(float objPos, float targetPos, float time) {
	return objPos + (targetPos - objPos) * time;
}

Vector3 Normalize(Vector3 v2) {
	Vector3 result;
	result.x = v2.x / sqrtf(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
	result.y = v2.y / sqrtf(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
	result.z = v2.z / sqrtf(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
	return result;
}

Matrix4x4 MakeViewportMatrix(
    float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result;
	result.m[0][0] = width / 2.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][1] = -(height / 2.0f);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0.0f;
	result.m[3][0] = left + width / 2;
	result.m[3][1] = top + height / 2;
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;
	return result;
}

Vector3 Transform(Vector3 vector, Matrix4x4 matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] +
	           1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] +
	           1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] +
	           1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] +
	          1.0f * matrix.m[3][3];
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

float Dot(const Vector3& v1, const Vector3& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

float Length(const Vector3& v) { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }

Vector3 Project(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {};
	float length = Dot(v2, v2);
	float dot = Dot(v1, v2);
	return Multiply(dot / length, v2);
}

Vector3 Multiply(const float& f, const Vector3& v) {
	Vector3 result;
	result.x = v.x * f;
	result.y = v.y * f;
	result.z = v.z * f;

	return result;
}

Vector3 Lerp(Vector3 objPos, Vector3 targetPos, float time) {
	Vector3 result;
	result.x = Lerp(objPos.x, targetPos.x, time);
	result.y = Lerp(objPos.y, targetPos.y, time);
	result.z = Lerp(objPos.z, targetPos.z, time);

	return result;
}
Vector3 Subtract(const Vector3& m1, const Vector3& m2) {
	Vector3 result;

	return result = {m1.x - m2.x, m1.y - m2.y, m1.z - m2.z};
}