#include "Vector3.h"

Vector3& operator+=(Vector3& m1, const Vector3& m2) {
	Vector3 result = {};
	result.x = m1.x + m2.x;
	result.y = m1.y + m2.y;
	result.z = m1.z + m2.z;

	m1 = result;
	return m1;
}

Vector3 operator+(const Vector3& m1, const Vector3& m2) {
	Vector3 result = m1;

	return result += m2;
}
Vector3& operator-=(Vector3& m1, const Vector3& m2) {
	Vector3 result = {};
	result.x = m1.x - m2.x;
	result.y = m1.y - m2.y;
	result.z = m1.z - m2.z;

	m1 = result;
	return m1;
}

Vector3 operator-(const Vector3& m1, const Vector3& m2) {
	Vector3 result = m1;

	return result -= m2;
}

Vector3& operator*=(Vector3& m1, const float m2) {
	Vector3 result = {};
	result.x = m1.x * m2;
	result.y = m1.y * m2;
	result.z = m1.z * m2;

	m1 = result;
	return m1;
}

Vector3 operator*(const Vector3& m1, const float m2) {
	Vector3 result = m1;
	return result *= m2;
}

Vector3& operator+=(Vector3& m1, const float m2) {
	Vector3 result = {};
	result.x = m1.x + m2;
	result.y = m1.y + m2;
	result.z = m1.z + m2;

	m1 = result;
	return m1;
}

Vector3 operator+(const Vector3& m1, const float m2) {
	Vector3 result = m1;
	return result += m2;
}

Vector3& operator*=(Vector3& m1, const Vector3 m2) {
	Vector3 result = {};
	result.x = m1.x * m2.x;
	result.y = m1.y * m2.y;
	result.z = m1.z * m2.z;

	m1 = result;
	return m1;
}

Vector3 operator*(const Vector3& m1, const Vector3 m2) {

	Vector3 result = m1;
	return result -= m2;
}
