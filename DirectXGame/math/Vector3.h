#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;
};

Vector3& operator+=(Vector3& m1, const Vector3& m2);
Vector3 operator+(const Vector3& m1, const Vector3& m2);
Vector3& operator-=(Vector3& m1, const Vector3& m2);
Vector3 operator-(const Vector3& m1, const Vector3& m2);
Vector3& operator*=(Vector3& m1, const float m2);
Vector3 operator*(const Vector3& m1, const float m2);
Vector3& operator+=(Vector3& m1, const float m2);
Vector3 operator+(const Vector3& m1, const float m2);
Vector3& operator*=(Vector3& m1, const Vector3 m2);
Vector3 operator*(const Vector3& m1, const Vector3 m2);