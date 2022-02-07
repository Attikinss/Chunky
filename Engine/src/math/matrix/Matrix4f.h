#pragma once
#include "math/vector/Vector3f.h"
#include "math/vector/Vector4f.h"

#include "Matrix3f.h"

struct Matrix4f
{
	Vector4f Value[4];

	Matrix4f()
	{
		Value[0] = { 1.0f, 0.0f, 0.0f, 0.0f };
		Value[1] = { 0.0f, 1.0f, 0.0f, 0.0f };
		Value[2] = { 0.0f, 0.0f, 1.0f, 0.0f };
		Value[3] = { 0.0f, 0.0f, 0.0f, 1.0f };
	}

	Matrix4f(float val)
	{
		Value[0] = { val,  0.0f, 0.0f, 0.0f };
		Value[1] = { 0.0f, val,  0.0f, 0.0f };
		Value[2] = { 0.0f, 0.0f, val,  0.0f };
		Value[3] = { 0.0f, 0.0f, 0.0f, val };
	}

	Matrix4f(const Matrix4f& matrix)
	{
		Value[0] = matrix[0];
		Value[1] = matrix[1];
		Value[2] = matrix[2];
		Value[3] = matrix[3];
	}

	Matrix4f(float x0, float y0, float z0, float w0, float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3)
	{
		Value[0] = { x0, y0, z0, w0 };
		Value[1] = { x1, y1, z1, w1 };
		Value[2] = { x2, y2, z2, w2 };
		Value[3] = { x3, y3, z3, w3 };
	}

	Matrix4f(const Vector4f& v0, const Vector4f& v1, const Vector4f& v2, const Vector4f& v3)
	{
		Value[0] = v0;
		Value[1] = v1;
		Value[2] = v2;
		Value[3] = v3;
	}

	Matrix4f::Matrix4f(const Matrix3f& matrix)
	{
		this->Value[0] = { matrix[0].x, matrix[0].y, matrix[0].z, 0.0f };
		this->Value[1] = { matrix[1].x, matrix[1].y, matrix[1].z, 0.0f };
		this->Value[2] = { matrix[2].x, matrix[2].y, matrix[2].z, 0.0f };
		this->Value[3] = { 0.0f, 0.0f, 0.0f, 1.0f };
	}

	Matrix3f ToMatrix3()
	{
		return Matrix3f
		{
			this->Value[0].x, this->Value[0].y, this->Value[0].z,
			this->Value[1].x, this->Value[1].y, this->Value[1].z,
			this->Value[2].x, this->Value[2].y, this->Value[2].z
		};
	}

	static Matrix4f Inverse(const Matrix4f& matrix)
	{
		float coef00 = matrix[2][2] * matrix[3][3] - matrix[3][2] * matrix[2][3];
		float coef02 = matrix[1][2] * matrix[3][3] - matrix[3][2] * matrix[1][3];
		float coef03 = matrix[1][2] * matrix[2][3] - matrix[2][2] * matrix[1][3];

		float coef04 = matrix[2][1] * matrix[3][3] - matrix[3][1] * matrix[2][3];
		float coef06 = matrix[1][1] * matrix[3][3] - matrix[3][1] * matrix[1][3];
		float coef07 = matrix[1][1] * matrix[2][3] - matrix[2][1] * matrix[1][3];

		float coef08 = matrix[2][1] * matrix[3][2] - matrix[3][1] * matrix[2][2];
		float coef10 = matrix[1][1] * matrix[3][2] - matrix[3][1] * matrix[1][2];
		float coef11 = matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2];

		float coef12 = matrix[2][0] * matrix[3][3] - matrix[3][0] * matrix[2][3];
		float coef14 = matrix[1][0] * matrix[3][3] - matrix[3][0] * matrix[1][3];
		float coef15 = matrix[1][0] * matrix[2][3] - matrix[2][0] * matrix[1][3];

		float coef16 = matrix[2][0] * matrix[3][2] - matrix[3][0] * matrix[2][2];
		float coef18 = matrix[1][0] * matrix[3][2] - matrix[3][0] * matrix[1][2];
		float coef19 = matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2];

		float coef20 = matrix[2][0] * matrix[3][1] - matrix[3][0] * matrix[2][1];
		float coef22 = matrix[1][0] * matrix[3][1] - matrix[3][0] * matrix[1][1];
		float coef23 = matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1];

		Vector4f fac0(coef00, coef00, coef02, coef03);
		Vector4f fac1(coef04, coef04, coef06, coef07);
		Vector4f fac2(coef08, coef08, coef10, coef11);
		Vector4f fac3(coef12, coef12, coef14, coef15);
		Vector4f fac4(coef16, coef16, coef18, coef19);
		Vector4f fac5(coef20, coef20, coef22, coef23);

		Vector4f vec0(matrix[1][0], matrix[0][0], matrix[0][0], matrix[0][0]);
		Vector4f vec1(matrix[1][1], matrix[0][1], matrix[0][1], matrix[0][1]);
		Vector4f vec2(matrix[1][2], matrix[0][2], matrix[0][2], matrix[0][2]);
		Vector4f vec3(matrix[1][3], matrix[0][3], matrix[0][3], matrix[0][3]);

		Vector4f inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
		Vector4f inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
		Vector4f inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
		Vector4f inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

		Vector4f signA(+1, -1, +1, -1);
		Vector4f signB(-1, +1, -1, +1);
		Matrix4f inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

		Vector4f row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

		Vector4f dot0(matrix[0] * row0);
		float dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);

		float oneOverDeterminant = 1.0f / dot1;
		inverse *= oneOverDeterminant;
		return inverse;
	}

	static Matrix4f LookAt(const Vector3f& position, const Vector3f& target, const Vector3f& up)
	{
		auto a = (target - position);

		Vector3f f = a.GetNormalised();
		Vector3f s = Vector3f::Cross(f, up);
		Vector3f u = Vector3f::Cross(s, f);

		Matrix4f result(1.0f);
		result[0][0] = s.x;
		result[1][0] = s.y;
		result[2][0] = s.z;
		result[0][1] = u.x;
		result[1][1] = u.y;
		result[2][1] = u.z;
		result[0][2] = -f.x;
		result[1][2] = -f.y;
		result[2][2] = -f.z;
		result[3][0] = -Vector3f::Dot(s, position);
		result[3][1] = -Vector3f::Dot(u, position);
		result[3][2] = Vector3f::Dot(f, position);

		return result;
	}

	static Matrix4f Orthographic(float leftBound, float rightBound, float lowerBound, float upperBound, float nearPlane, float farPlane)
	{
		Matrix4f result(1.0f);
		result[0][0] = 2.0f / (rightBound - leftBound);
		result[1][1] = 2.0f / (upperBound - lowerBound);
		result[2][2] = -2.0f / (farPlane - nearPlane);
		result[3][0] = -(rightBound + leftBound) / (rightBound - leftBound);
		result[3][1] = -(upperBound + lowerBound) / (upperBound - lowerBound);
		result[3][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);

		return result;
	}

	static Matrix4f Perspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
	{
		// TODO: _ASSERT(Math::Abs(aspectRatio - Math::Epsilon) > 0);

		float tanHalfFOV = (float)Math::Tan(fieldOfView / 2.0f);

		Matrix4f result(0.0f);
		result[0][0] = 1.0f / (aspectRatio * tanHalfFOV);
		result[1][1] = 1.0f / (tanHalfFOV);
		result[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
		result[2][3] = -1.0f;
		result[3][2] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);

		return result;
	}

	static Matrix4f Rotate(const Matrix4f& matrix, float angle, const Vector3f& vector)
	{
		auto vec = vector;
		const float cos = (float)Math::Cos(angle);
		const float sin = (float)Math::Sin(angle);

		Vector3f axis = vec.GetNormalised() * -1.0f;
		Vector3f temp((1.0f - cos) * axis);

		Matrix4f rotation;
		rotation[0][0] = cos + temp[0] * axis[0];
		rotation[0][1] = temp[0] * axis[1] + sin * axis[2];
		rotation[0][2] = temp[0] * axis[2] - sin * axis[1];

		rotation[1][0] = temp[1] * axis[0] - sin * axis[2];
		rotation[1][1] = cos + temp[1] * axis[1];
		rotation[1][2] = temp[1] * axis[2] + sin * axis[0];

		rotation[2][0] = temp[2] * axis[0] + sin * axis[1];
		rotation[2][1] = temp[2] * axis[1] - sin * axis[0];
		rotation[2][2] = cos + temp[2] * axis[2];

		Matrix4f result;
		result[0] = matrix[0] * rotation[0][0] + matrix[1] * rotation[0][1] + matrix[2] * rotation[0][2];
		result[1] = matrix[0] * rotation[1][0] + matrix[1] * rotation[1][1] + matrix[2] * rotation[1][2];
		result[2] = matrix[0] * rotation[2][0] + matrix[1] * rotation[2][1] + matrix[2] * rotation[2][2];
		result[3] = matrix[3];

		return result;
	}

	static Matrix4f Scale(const Matrix4f& matrix, const Vector3f& vector)
	{
		Matrix4f result;
		result[0] = matrix[0] * vector[0];
		result[1] = matrix[1] * vector[1];
		result[2] = matrix[2] * vector[2];
		result[3] = matrix[3];

		return result;
	}

	static Matrix4f Translate(const Matrix4f& matrix, const Vector3f& vector)
	{
		Matrix4f result(matrix);
		result[3] = matrix[0] * vector[0] +
					matrix[1] * vector[1] +
					matrix[2] * -vector[2] +
					matrix[3];

		return result;
	}

	static Matrix4f Transpose(const Matrix4f& matrix)
	{
		Matrix4f result;
		result[0][0] = matrix[0][0];
		result[0][1] = matrix[1][0];
		result[0][2] = matrix[2][0];
		result[0][3] = matrix[3][0];

		result[1][0] = matrix[0][1];
		result[1][1] = matrix[1][1];
		result[1][2] = matrix[2][1];
		result[1][3] = matrix[3][1];

		result[2][0] = matrix[0][2];
		result[2][1] = matrix[1][2];
		result[2][2] = matrix[2][2];
		result[2][3] = matrix[3][2];

		result[3][0] = matrix[0][3];
		result[3][1] = matrix[1][3];
		result[3][2] = matrix[2][3];
		result[3][3] = matrix[3][3];

		return result;
	}

#pragma region Operator Overloads
	Matrix4f operator+(const Matrix4f& other)
	{
		return Matrix4f(this->Value[0] + other[0], this->Value[1] + other[1], this->Value[2] + other[2], this->Value[3] + other[3]);
	}

	Matrix4f operator-(const Matrix4f& other)
	{
		return Matrix4f(this->Value[0] - other[0], this->Value[1] - other[1], this->Value[2] - other[2], this->Value[3] - other[3]);
	}

	Matrix4f operator*(const Matrix4f& other)
	{
		Matrix4f result;
		result[0] = this->Value[0] * other[0][0] + this->Value[1] * other[0][1] + this->Value[2] * other[0][2] + this->Value[3] * other[0][3];
		result[1] = this->Value[0] * other[1][0] + this->Value[1] * other[1][1] + this->Value[2] * other[1][2] + this->Value[3] * other[1][3];
		result[2] = this->Value[0] * other[2][0] + this->Value[1] * other[2][1] + this->Value[2] * other[2][2] + this->Value[3] * other[2][3];
		result[3] = this->Value[0] * other[3][0] + this->Value[1] * other[3][1] + this->Value[2] * other[3][2] + this->Value[3] * other[3][3];
		return result;
	}

	Matrix4f operator*(float scalar)
	{
		return Matrix4f(this->Value[0] * scalar, this->Value[1] * scalar, this->Value[2] * scalar, this->Value[3] * scalar);
	}

	Matrix4f& operator=(const Matrix4f& other)
	{
		this->Value[0] = other[0];
		this->Value[1] = other[1];
		this->Value[2] = other[2];
		this->Value[3] = other[3];
		return *this;
	}

	Matrix4f& operator+=(const Matrix4f& other)
	{
		this->Value[0] += other[0];
		this->Value[1] += other[1];
		this->Value[2] += other[2];
		this->Value[3] += other[3];
		return *this;
	}

	Matrix4f& operator-=(const Matrix4f& other)
	{
		this->Value[0] -= other[0];
		this->Value[1] -= other[1];
		this->Value[2] -= other[2];
		this->Value[3] -= other[3];
		return *this;
	}

	Matrix4f& operator*=(float scalar)
	{
		this->Value[0] *= scalar;
		this->Value[1] *= scalar;
		this->Value[2] *= scalar;
		this->Value[3] *= scalar;
		return *this;
	}

	Matrix4f& operator*=(const Matrix4f& other)
	{
		return (*this = *this * other);
	}

	Matrix4f& operator/=(float scalar)
	{
		this->Value[0] /= scalar;
		this->Value[1] /= scalar;
		this->Value[2] /= scalar;
		this->Value[3] /= scalar;
		return *this;
	}

	Matrix4f& operator/=(const Matrix4f& other)
	{
		return *this *= Inverse(other);
	}

	Matrix4f& operator++()
	{
		this->Value[0]++;
		this->Value[1]++;
		this->Value[2]++;
		this->Value[3]++;
		return *this;
	}

	Matrix4f& operator--()
	{
		this->Value[0]--;
		this->Value[1]--;
		this->Value[2]--;
		this->Value[3]--;
		return *this;
	}

	Matrix4f operator++(int)
	{
		Matrix4f result(*this);
		++* this;
		return result;
	}

	Matrix4f operator--(int)
	{
		Matrix4f result(*this);
		--* this;
		return result;
	}

	Vector4f operator*(const Vector4f& vector)
	{
		return Vector4f(
			vector[0] * this->Value[0][0] + vector[1] * this->Value[1][0] + vector[2] * this->Value[2][0] + vector[3] * this->Value[3][0],
			vector[0] * this->Value[0][1] + vector[1] * this->Value[1][1] + vector[2] * this->Value[2][1] + vector[3] * this->Value[3][1],
			vector[0] * this->Value[0][2] + vector[1] * this->Value[1][2] + vector[2] * this->Value[2][2] + vector[3] * this->Value[3][2],
			vector[0] * this->Value[0][3] + vector[1] * this->Value[1][3] + vector[2] * this->Value[2][3] + vector[3] * this->Value[3][3]);
	}

	Vector4f operator/(const Vector4f& vector)
	{
		return Matrix4f::Inverse(*this) * vector;
	}

	Vector4f& operator[](int index)
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 3);
		return Value[index];
	}

	const Vector4f& operator[](int index) const
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 3);
		return Value[index];
	}

	bool operator==(const Matrix4f& other)
	{
		return (this->Value[0] == other[0]) && (this->Value[1] == other[1]) && (this->Value[2] == other[2]);
	}

	bool operator!=(const Matrix4f& other)
	{
		return !(*this == other);
	}
#pragma endregion
};