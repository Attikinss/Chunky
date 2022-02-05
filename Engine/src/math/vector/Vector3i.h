#pragma once
#include "math/Math.h"

struct Vector3i
{
	const static Vector3i Zero;
	const static Vector3i One;
	const static Vector3i Up;
	const static Vector3i Down;
	const static Vector3i Left;
	const static Vector3i Right;
	const static Vector3i Forward;
	const static Vector3i Back;

	int x = 0;
	int y = 0;
	int z = 0;

	Vector3i() = default;
	Vector3i(int val)
		: x(val), y(val), z(val) { }
	Vector3i(int x, int y, int z)
		: x(x), y(y), z(z) { }
	Vector3i(const Vector3i& other)
		: x(other.x), y(other.y), z(other.z) { }

	Vector3i GetNormalised()
	{
		int magnitude = Math::RoundToInt(Magnitude());
		Vector3i result = (magnitude != 0) ? (*this / magnitude) : Vector3i::Zero;
		return result;
	}

	static double DistanceSqr(const Vector3i& a, const Vector3i& b)
	{
		double diffX = (double)a.x - b.x;
		double diffY = (double)a.y - b.y;
		double diffZ = (double)a.z - b.z;
		return diffX * diffX + diffY * diffY + diffZ * diffZ;
	}

	double MagnitudeSqr() const { return (double)x * x + (double)y * y + (double)z * z; }
	double Magnitude() const { return Math::Sqrt(MagnitudeSqr()); }
	static double Distance(const Vector3i& a, const Vector3i& b) { return Math::Sqrt(DistanceSqr(a, b)); }
	static double Dot(const Vector3i& a, const Vector3i& b) { return (double)a.x * b.x + (double)a.y * b.y + (double)a.z * b.z; }
	static Vector3i Cross(const Vector3i& a, const Vector3i& b) { return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }

#pragma region Operator Overloads

	Vector3i operator=(const Vector3i& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	Vector3i operator/(int val)
	{
		return Vector3i(x / val, y / val, z / val);
	}

	Vector3i operator+=(const Vector3i& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3i operator-=(const Vector3i& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3i operator*=(int val)
	{
		x *= val;
		y *= val;
		z *= val;
		return *this;
	}

	Vector3i operator*=(Vector3i other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	Vector3i operator/=(int val)
	{
		x /= val;
		y /= val;
		z /= val;
		return *this;
	}

	Vector3i operator++()
	{
		x++;
		y++;
		z++;
		return *this;
	}

	Vector3i operator--()
	{
		x--;
		y--;
		z--;
		return *this;
	}

	Vector3i operator++(int)
	{
		Vector3i result(*this);
		++* this;
		return result;
	}

	int& operator[](int index)
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 3);
		return (&x)[index];
	}

	const int& operator[](int index) const
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 3);
		return (&x)[index];
	}

	bool operator==(const Vector3i& other)
	{
		return (this[0] == other[0]) && (this[1] == other[1] && (this[2] == other[2]));
	}

	bool operator!=(const Vector3i& other)
	{
		return !(*this == other);
	}

#pragma endregion
};

Vector3i operator+(const Vector3i& a, const Vector3i& b);
Vector3i operator-(const Vector3i& a, const Vector3i& b);
Vector3i operator*(const Vector3i& a, const Vector3i& b);
Vector3i operator*(const Vector3i& vec, int val);