#pragma once
#include "math/vector/Vector3.h"
#include "math/vector/Vector4.h"

#include "Matrix3.h"

struct Matrix4
{
	Vector4 Value[4];

	Matrix4()
	{
		Value[0] = { 1.0, 0.0, 0.0, 0.0 };
		Value[1] = { 0.0, 1.0, 0.0, 0.0 };
		Value[2] = { 0.0, 0.0, 1.0, 0.0 };
		Value[3] = { 0.0, 0.0, 0.0, 1.0 };
	}

	Matrix4(double val)
	{
		Value[0] = { val, 0.0, 0.0, 0.0 };
		Value[1] = { 0.0, val, 0.0, 0.0 };
		Value[2] = { 0.0, 0.0, val, 0.0 };
		Value[3] = { 0.0, 0.0, 0.0, val };
	}

	Matrix4(const Matrix4& matrix)
	{
		Value[0] = matrix[0];
		Value[1] = matrix[1];
		Value[2] = matrix[2];
		Value[3] = matrix[3];
	}

	Matrix4(double x0, double y0, double z0, double w0, double x1, double y1, double z1, double w1, double x2, double y2, double z2, double w2, double x3, double y3, double z3, double w3)
	{
		Value[0] = { x0, y0, z0, w0 };
		Value[1] = { x1, y1, z1, w1 };
		Value[2] = { x2, y2, z2, w2 };
		Value[3] = { x3, y3, z3, w3 };
	}

	Matrix4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3)
	{
		Value[0] = v0;
		Value[1] = v1;
		Value[2] = v2;
		Value[3] = v3;
	}

	Matrix4::Matrix4(const Matrix3& matrix)
	{
		this->Value[0] = { matrix[0].x, matrix[0].y, matrix[0].z, 0.0f };
		this->Value[1] = { matrix[1].x, matrix[1].y, matrix[1].z, 0.0f };
		this->Value[2] = { matrix[2].x, matrix[2].y, matrix[2].z, 0.0f };
		this->Value[3] = { 0.0f, 0.0f, 0.0f, 1.0f };
	}

	Matrix3 ToMatrix3()
	{
		return Matrix3
		{
			this->Value[0].x, this->Value[0].y, this->Value[0].z,
			this->Value[1].x, this->Value[1].y, this->Value[1].z,
			this->Value[2].x, this->Value[2].y, this->Value[2].z
		};
	}

	static Matrix4 Inverse(const Matrix4& matrix)
	{
		double coef00 = matrix[2][2] * matrix[3][3] - matrix[3][2] * matrix[2][3];
		double coef02 = matrix[1][2] * matrix[3][3] - matrix[3][2] * matrix[1][3];
		double coef03 = matrix[1][2] * matrix[2][3] - matrix[2][2] * matrix[1][3];

		double coef04 = matrix[2][1] * matrix[3][3] - matrix[3][1] * matrix[2][3];
		double coef06 = matrix[1][1] * matrix[3][3] - matrix[3][1] * matrix[1][3];
		double coef07 = matrix[1][1] * matrix[2][3] - matrix[2][1] * matrix[1][3];

		double coef08 = matrix[2][1] * matrix[3][2] - matrix[3][1] * matrix[2][2];
		double coef10 = matrix[1][1] * matrix[3][2] - matrix[3][1] * matrix[1][2];
		double coef11 = matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2];

		double coef12 = matrix[2][0] * matrix[3][3] - matrix[3][0] * matrix[2][3];
		double coef14 = matrix[1][0] * matrix[3][3] - matrix[3][0] * matrix[1][3];
		double coef15 = matrix[1][0] * matrix[2][3] - matrix[2][0] * matrix[1][3];

		double coef16 = matrix[2][0] * matrix[3][2] - matrix[3][0] * matrix[2][2];
		double coef18 = matrix[1][0] * matrix[3][2] - matrix[3][0] * matrix[1][2];
		double coef19 = matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2];

		double coef20 = matrix[2][0] * matrix[3][1] - matrix[3][0] * matrix[2][1];
		double coef22 = matrix[1][0] * matrix[3][1] - matrix[3][0] * matrix[1][1];
		double coef23 = matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1];

		Vector4 fac0(coef00, coef00, coef02, coef03);
		Vector4 fac1(coef04, coef04, coef06, coef07);
		Vector4 fac2(coef08, coef08, coef10, coef11);
		Vector4 fac3(coef12, coef12, coef14, coef15);
		Vector4 fac4(coef16, coef16, coef18, coef19);
		Vector4 fac5(coef20, coef20, coef22, coef23);

		Vector4 vec0(matrix[1][0], matrix[0][0], matrix[0][0], matrix[0][0]);
		Vector4 vec1(matrix[1][1], matrix[0][1], matrix[0][1], matrix[0][1]);
		Vector4 vec2(matrix[1][2], matrix[0][2], matrix[0][2], matrix[0][2]);
		Vector4 vec3(matrix[1][3], matrix[0][3], matrix[0][3], matrix[0][3]);

		Vector4 inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
		Vector4 inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
		Vector4 inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
		Vector4 inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

		Vector4 signA(+1, -1, +1, -1);
		Vector4 signB(-1, +1, -1, +1);
		Matrix4 inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

		Vector4 row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

		Vector4 dot0(matrix[0] * row0);
		double dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);

		double oneOverDeterminant = 1.0 / dot1;
		inverse *= oneOverDeterminant;
		return inverse;
	}

	static Matrix4 LookAt(const Vector3& position, const Vector3& target, const Vector3& up)
	{
		auto a = (target - position);

		Vector3 f = a.GetNormalised();
		Vector3 s = Vector3::Cross(f, up);
		Vector3 u = Vector3::Cross(s, f);

		Matrix4 result(1.0);
		result[0][0] = s.x;
		result[1][0] = s.y;
		result[2][0] = s.z;
		result[0][1] = u.x;
		result[1][1] = u.y;
		result[2][1] = u.z;
		result[0][2] = -f.x;
		result[1][2] = -f.y;
		result[2][2] = -f.z;
		result[3][0] = -Vector3::Dot(s, position);
		result[3][1] = -Vector3::Dot(u, position);
		result[3][2] = Vector3::Dot(f, position);

		return result;
	}

	static Matrix4 Orthographic(double leftBound, double rightBound, double lowerBound, double upperBound, double nearPlane, double farPlane)
	{
		Matrix4 result(1.0);
		result[0][0] =  2.0 / (rightBound - leftBound);
		result[1][1] =  2.0 / (upperBound - lowerBound);
		result[2][2] = -2.0 / (farPlane - nearPlane);
		result[3][0] = -(rightBound + leftBound) / (rightBound - leftBound);
		result[3][1] = -(upperBound + lowerBound) / (upperBound - lowerBound);
		result[3][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);

		return result;
	}

	static Matrix4 Perspective(double fieldOfView, double aspectRatio, double nearPlane, double farPlane)
	{
		// TODO: _ASSERT(Math::Abs(aspectRatio - Math::Epsilon) > 0);

		double tanHalfFOV = Math::Tan(fieldOfView / 2.0);

		Matrix4 result(0.0);
		result[0][0] = 1.0 / (aspectRatio * tanHalfFOV);
		result[1][1] = 1.0 / (tanHalfFOV);
		result[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
		result[2][3] = -1.0;
		result[3][2] = -(2.0 * farPlane * nearPlane) / (farPlane - nearPlane);

		return result;
	}

	static Matrix4 Rotate(const Matrix4& matrix, double angle, const Vector3& vector)
	{
		auto vec = vector;
		const double cos = Math::Cos(angle);
		const double sin = Math::Sin(angle);

		Vector3 axis = vec.GetNormalised();
		Vector3 temp((1.0 - cos) * axis);

		Matrix4 rotation;
		rotation[0][0] = cos + temp[0] * axis[0];
		rotation[0][1] = temp[0] * axis[1] + sin * axis[2];
		rotation[0][2] = temp[0] * axis[2] - sin * axis[1];

		rotation[1][0] = temp[1] * axis[0] - sin * axis[2];
		rotation[1][1] = cos + temp[1] * axis[1];
		rotation[1][2] = temp[1] * axis[2] + sin * axis[0];

		rotation[2][0] = temp[2] * axis[0] + sin * axis[1];
		rotation[2][1] = temp[2] * axis[1] - sin * axis[0];
		rotation[2][2] = cos + temp[2] * axis[2];

		Matrix4 result;
		result[0] = matrix[0] * rotation[0][0] + matrix[1] * rotation[0][1] + matrix[2] * rotation[0][2];
		result[1] = matrix[0] * rotation[1][0] + matrix[1] * rotation[1][1] + matrix[2] * rotation[1][2];
		result[2] = matrix[0] * rotation[2][0] + matrix[1] * rotation[2][1] + matrix[2] * rotation[2][2];
		result[3] = matrix[3];

		return result;
	}

	static Matrix4 Scale(const Matrix4& matrix, const Vector3& vector)
	{
		Matrix4 result;
		result[0] = matrix[0] * vector[0];
		result[1] = matrix[1] * vector[1];
		result[2] = matrix[2] * vector[2];
		result[3] = matrix[3];

		return result;
	}

	static Matrix4 Translate(const Matrix4& matrix, const Vector3& vector)
	{
		Matrix4 result(matrix);
		result[3] = matrix[0] * vector[0] +
					matrix[1] * vector[1] +
					matrix[2] * -vector[2] +
					matrix[3];

		return result;
	}

	static Matrix4 Transpose(const Matrix4& matrix)
	{
		Matrix4 result;
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
	Matrix4 operator+(const Matrix4& other)
	{
		return Matrix4(this->Value[0] + other[0], this->Value[1] + other[1], this->Value[2] + other[2], this->Value[3] + other[3]);
	}

	Matrix4 operator-(const Matrix4& other)
	{
		return Matrix4(this->Value[0] - other[0], this->Value[1] - other[1], this->Value[2] - other[2], this->Value[3] - other[3]);
	}

	Matrix4 operator*(const Matrix4& other)
	{
		Matrix4 result;
		result[0] = this->Value[0] * other[0][0] + this->Value[1] * other[0][1] + this->Value[2] * other[0][2] + this->Value[3] * other[0][3];
		result[1] = this->Value[0] * other[1][0] + this->Value[1] * other[1][1] + this->Value[2] * other[1][2] + this->Value[3] * other[1][3];
		result[2] = this->Value[0] * other[2][0] + this->Value[1] * other[2][1] + this->Value[2] * other[2][2] + this->Value[3] * other[2][3];
		result[3] = this->Value[0] * other[3][0] + this->Value[1] * other[3][1] + this->Value[2] * other[3][2] + this->Value[3] * other[3][3];
		return result;
	}

	Matrix4 operator*(double scalar)
	{
		return Matrix4(this->Value[0] * scalar, this->Value[1] * scalar, this->Value[2] * scalar, this->Value[3] * scalar);
	}

	Matrix4& operator=(const Matrix4& other)
	{
		this->Value[0] = other[0];
		this->Value[1] = other[1];
		this->Value[2] = other[2];
		return *this;
	}

	Matrix4& operator+=(const Matrix4& other)
	{
		this->Value[0] += other[0];
		this->Value[1] += other[1];
		this->Value[2] += other[2];
		return *this;
	}

	Matrix4& operator-=(const Matrix4& other)
	{
		this->Value[0] -= other[0];
		this->Value[1] -= other[1];
		this->Value[2] -= other[2];
		return *this;
	}

	Matrix4& operator*=(double scalar)
	{
		this->Value[0] *= scalar;
		this->Value[1] *= scalar;
		this->Value[2] *= scalar;
		return *this;
	}

	Matrix4& operator*=(const Matrix4& other)
	{
		return (*this = *this * other);
	}

	Matrix4& operator/=(double scalar)
	{
		this->Value[0] /= scalar;
		this->Value[1] /= scalar;
		this->Value[2] /= scalar;
		return *this;
	}

	Matrix4& operator/=(const Matrix4& other)
	{
		return *this *= Inverse(other);
	}

	Matrix4& operator++()
	{
		this->Value[0]++;
		this->Value[1]++;
		this->Value[2]++;
		return *this;
	}

	Matrix4& operator--()
	{
		this->Value[0]--;
		this->Value[1]--;
		this->Value[2]--;
		return *this;
	}

	Matrix4 operator++(int)
	{
		Matrix4 result(*this);
		++*this;
		return result;
	}

	Matrix4 operator--(int)
	{
		Matrix4 result(*this);
		--*this;
		return result;
	}

	Vector4 operator*(const Vector4& vector)
	{
		return Vector4(
			vector[0] * this->Value[0][0] + vector[1] * this->Value[1][0] + vector[2] * this->Value[2][0] + vector[3] * this->Value[3][0],
			vector[0] * this->Value[0][1] + vector[1] * this->Value[1][1] + vector[2] * this->Value[2][1] + vector[3] * this->Value[3][1],
			vector[0] * this->Value[0][2] + vector[1] * this->Value[1][2] + vector[2] * this->Value[2][2] + vector[3] * this->Value[3][2],
			vector[0] * this->Value[0][3] + vector[1] * this->Value[1][3] + vector[2] * this->Value[2][3] + vector[3] * this->Value[3][3]);
	}

	Vector4 operator/(const Vector4& vector)
	{
		return Matrix4::Inverse(*this) * vector;
	}

	Vector4& operator[](int index)
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 3);
		return Value[index];
	}

	const Vector4& operator[](int index) const
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 3);
		return Value[index];
	}

	bool operator==(const Matrix4& other)
	{
		return (this->Value[0] == other[0]) && (this->Value[1] == other[1]) && (this->Value[2] == other[2]);
	}

	bool operator!=(const Matrix4& other)
	{
		return !(*this == other);
	}
#pragma endregion
};