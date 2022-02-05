#pragma once
#include "math/vector/Vector3f.h"

struct Matrix3f
{
	Vector3f Value[3];

	Matrix3f()
	{
		Value[0] = { 1.0f, 0.0f, 0.0f };
		Value[1] = { 0.0f, 1.0f, 0.0f };
		Value[2] = { 0.0f, 0.0f, 1.0f };
	}

	Matrix3f(float val)
	{
		Value[0] = { val,  0.0f, 0.0f };
		Value[1] = { 0.0f, val,  0.0f };
		Value[2] = { 0.0f, 0.0f, val };
	}

	Matrix3f(const Matrix3f& matrix)
	{
		Value[0] = matrix[0];
		Value[1] = matrix[1];
		Value[2] = matrix[2];
	}

	Matrix3f(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2)
	{
		Value[0] = { x0, y0, z0 };
		Value[1] = { x1, y1, z1 };
		Value[2] = { x2, y2, z2 };
	}

	Matrix3f(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2)
	{
		Value[0] = v0;
		Value[1] = v1;
		Value[2] = v2;
	}

	static Matrix3f Inverse(const Matrix3f& matrix)
	{
		float oneOverDeterminant = 1.0f / (
			+matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2])
			- matrix[1][0] * (matrix[0][1] * matrix[2][2] - matrix[2][1] * matrix[0][2])
			+ matrix[2][0] * (matrix[0][1] * matrix[1][2] - matrix[1][1] * matrix[0][2]));

		Matrix3f inverse;
		inverse[0][0] = +(matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]) * oneOverDeterminant;
		inverse[1][0] = -(matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2]) * oneOverDeterminant;
		inverse[2][0] = +(matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1]) * oneOverDeterminant;
		inverse[0][1] = -(matrix[0][1] * matrix[2][2] - matrix[2][1] * matrix[0][2]) * oneOverDeterminant;
		inverse[1][1] = +(matrix[0][0] * matrix[2][2] - matrix[2][0] * matrix[0][2]) * oneOverDeterminant;
		inverse[2][1] = -(matrix[0][0] * matrix[2][1] - matrix[2][0] * matrix[0][1]) * oneOverDeterminant;
		inverse[0][2] = +(matrix[0][1] * matrix[1][2] - matrix[1][1] * matrix[0][2]) * oneOverDeterminant;
		inverse[1][2] = -(matrix[0][0] * matrix[1][2] - matrix[1][0] * matrix[0][2]) * oneOverDeterminant;
		inverse[2][2] = +(matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]) * oneOverDeterminant;

		return inverse;
	}

	static Matrix3f Transpose(const Matrix3f& matrix)
	{
		Matrix3f result;
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

		return result;
	}

#pragma region Operator Overloads
	Matrix3f operator+(const Matrix3f& other)
	{
		return Matrix3f(Value[0] + other[0], Value[1] + other[1], Value[2] + other[2]);
	}

	Matrix3f operator-(const Matrix3f& other)
	{
		return Matrix3f(Value[0] - other[0], Value[1] - other[1], Value[2] - other[2]);
	}

	Matrix3f& operator=(const Matrix3f& other)
	{
		this->Value[0] = other[0];
		this->Value[1] = other[1];
		this->Value[2] = other[2];
		return *this;
	}

	Matrix3f& operator+=(const Matrix3f& other)
	{
		this->Value[0] += other[0];
		this->Value[1] += other[1];
		this->Value[2] += other[2];
		return *this;
	}

	Matrix3f& operator-=(const Matrix3f& other)
	{
		this->Value[0] -= other[0];
		this->Value[1] -= other[1];
		this->Value[2] -= other[2];
		return *this;
	}

	Matrix3f& operator*=(float scalar)
	{
		this->Value[0] *= scalar;
		this->Value[1] *= scalar;
		this->Value[2] *= scalar;
		return *this;
	}

	Matrix3f& operator/=(float scalar)
	{
		this->Value[0] /= scalar;
		this->Value[1] /= scalar;
		this->Value[2] /= scalar;
		return *this;
	}

	Matrix3f& operator++()
	{
		++this->Value[0];
		++this->Value[1];
		++this->Value[2];
		return *this;
	}

	Matrix3f& operator--()
	{
		--this->Value[0];
		--this->Value[1];
		--this->Value[2];
		return *this;
	}

	Matrix3f operator++(int)
	{
		++this->Value[0];
		++this->Value[1];
		++this->Value[2];
		return *this;
	}

	Matrix3f operator--(int)
	{
		--this->Value[0];
		--this->Value[1];
		--this->Value[2];
		return *this;
	}

	Vector3f& operator[](int index)
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 3);
		return Value[index];
	}

	const Vector3f& operator[](int index) const
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 3);
		return Value[index];
	}

	bool operator==(const Matrix3f& other)
	{
		return (this->Value[0] == other[0]) && (this->Value[1] == other[1]) && (this->Value[2] == other[2]);
	}

	bool operator!=(const Matrix3f& other)
	{
		return !(*this == other);
	}
#pragma endregion
};