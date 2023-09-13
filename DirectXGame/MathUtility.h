#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Vector2.h"

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);
Matrix4x4 Inverse(const Matrix4x4& matrix);
float Lerp(float objPos, float targetPos, float time);
Vector3 Normalize(Vector3 v2);
Matrix4x4 MakeViewportMatrix(
    float left, float top, float width, float height, float minDepth, float maxDepth);
Vector3 Transform(Vector3 vector, Matrix4x4 matrix);
float Dot(const Vector3& v1, const Vector3& v2);
float Length(const Vector3& v);
Vector3 Project(const Vector3& v1, const Vector3& v2);
Vector3 Multiply(const float& f, const Vector3& v);
Vector3 Lerp(Vector3 objPos, Vector3 targetPos, float time);
Vector2 LerpV2(Vector2 objPos, Vector2 targetPos, float time);
Vector3 Subtract(const Vector3& m1, const Vector3& m2);