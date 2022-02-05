#pragma once
#include "math/vector/Vector3.h"

struct Matrix3
{
	Vector3 Value[3];

	Matrix3()
	{
		Value[0] = { 1.0, 0.0, 0.0 };
		Value[1] = { 0.0, 1.0, 0.0 };
		Value[2] = { 0.0, 0.0, 1.0 };
	}

	Matrix3(double val)
	{
		Value[0] = { val, 0.0, 0.0 };
		Value[1] = { 0.0, val, 0.0 };
		Value[2] = { 0.0, 0.0, val };
	}

	Matrix3(const Matrix3& matrix)
	{
		Value[0] = matrix[0];
		Value[1] = matrix[1];
		Value[2] = matrix[2];
	}

	Matrix3(double x0, double y0, double z0, double x1, double y1, double z1, double x2, double y2, double z2)
	{
		Value[0] = { x0, y0, z0 };
		Value[1] = { x1, y1, z1 };
		Value[2] = { x2, y2, z2 };
	}

	Matrix3(const Vector3& v0, const Vector3& v1, const Vector3& v2)
	{
		Value[0] = v0;
		Value[1] = v1;
		Value[2] = v2;
	}

	static Matrix3 Inverse(const Matrix3& matrix)
	{
		double oneOverDeterminant = 1.0 / (
			+ matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2])
			- matrix[1][0] * (matrix[0][1] * matrix[2][2] - matrix[2][1] * matrix[0][2])
			+ matrix[2][0] * (matrix[0][1] * matrix[1][2] - matrix[1][1] * matrix[0][2]));

		Matrix3 inverse;
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

	static Matrix3 Transpose(const Matrix3& matrix)
	{
		Matrix3 result;
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
	Matrix3 operator+(const Matrix3& other)
	{
		return Matrix3(Value[0] + other[0], Value[1] + other[1], Value[2] + other[2]);
	}

	Matrix3 operator-(const Matrix3& other)
	{
		return Matrix3(Value[0] - other[0], Value[1] - other[1], Value[2] - other[2]);
	}

	Matrix3& operator=(const Matrix3& other)
	{
		this->Value[0] = other[0];
		this->Value[1] = other[1];
		this->Value[2] = other[2];
		return *this;
	}

	Matrix3& operator+=(const Matrix3& other)
	{
		this->Value[0] += other[0];
		this->Value[1] += other[1];
		this->Value[2] += other[2];
		return *this;
	}

	Matrix3& operator-=(const Matrix3& other)
	{
		this->Value[0] -= other[0];
		this->Value[1] -= other[1];
		this->Value[2] -= other[2];
		return *this;
	}

	Matrix3& operator*=(double scalar)
	{
		this->Value[0] *= scalar;
		this->Value[1] *= scalar;
		this->Value[2] *= scalar;
		return *this;
	}

	Matrix3& operator/=(double scalar)
	{
		this->Value[0] /= scalar;
		this->Value[1] /= scalar;
		this->Value[2] /= scalar;
		return *this;
	}

	Matrix3& operator++()
	{
		++this->Value[0];
		++this->Value[1];
		++this->Value[2];
		return *this;
	}

	Matrix3& operator--()
	{
		--this->Value[0];
		--this->Value[1];
		--this->Value[2];
		return *this;
	}

	Matrix3 operator++(int)
	{
		++this->Value[0];
		++this->Value[1];
		++this->Value[2];
		return *this;
	}

	Matrix3 operator--(int)
	{
		--this->Value[0];
		--this->Value[1];
		--this->Value[2];
		return *this;
	}

	Vector3& operator[](int index)
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 3);
		return Value[index];
	}

	const Vector3& operator[](int index) const
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 3);
		return Value[index];
	}

	bool operator==(const Matrix3& other)
	{
		return (this->Value[0] == other[0]) && (this->Value[1] == other[1]) && (this->Value[2] == other[2]);
	}

	bool operator!=(const Matrix3& other)
	{
		return !(*this == other);
	}
#pragma endregion
};