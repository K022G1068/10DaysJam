#include "Matrix4x4.h"

Matrix4x4& operator*=(Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			for (size_t k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	m1 = result;
	return m1;
}

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = m1;

	return result *= m2;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result;

	result = {
	    scale.x, 0.0f, 0.0f,    0.0f, 0.0f, scale.y, 0.0f, 0.0f,
	    0.0f,    0.0f, scale.z, 0.0f, 0.0f, 0.0f,    0.0f, 1.0f,
	};

	return result;
}

Matrix4x4 MakeRotationMatrixX(const float& theta) {
	Matrix4x4 result;
	float sin = sinf(theta);
	float cos = cosf(theta);

	result = {
	    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, cos, sin, 0.0f, 0.0f, -sin, cos, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	return result;
}

Matrix4x4 MakeRotationMatrixY(const float& theta) {
	Matrix4x4 result;
	float sin = sinf(theta);
	float cos = cosf(theta);

	result = {
	    cos, 0.0f, -sin, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, sin, 0.0f, cos, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	return result;
}

Matrix4x4 MakeRotationMatrixZ(const float& theta) {
	Matrix4x4 result;
	float sin = sinf(theta);
	float cos = cosf(theta);

	result = {
	    cos, sin, 0.0f, 0.0f, -sin, cos, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	return result;
}

Matrix4x4 MakeTransformMatrix(const Vector3& trans) {
	Matrix4x4 result;

	result = {
	    1.0f, 0.0f, 0.0f, 0.0f, 0.0f,    1.0f,    0.0f,    0.0f,
	    0.0f, 0.0f, 1.0f, 0.0f, trans.x, trans.y, trans.z, 1.0f,
	};

	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate) {
	Matrix4x4 m_scale = MakeScaleMatrix(scale);
	Matrix4x4 m_rotX = MakeRotationMatrixX(rot.x);
	Matrix4x4 m_rotY = MakeRotationMatrixY(rot.y);
	Matrix4x4 m_rotZ = MakeRotationMatrixZ(rot.z);

	Matrix4x4 m_rot = m_rotZ * m_rotX * m_rotY;

	Matrix4x4 m_trans = MakeTransformMatrix(translate);

	Matrix4x4 m_Affine = m_scale * m_rot * m_trans;

	return m_Affine;
}
