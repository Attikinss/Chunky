#pragma once
#include "math/Math.h"

struct Vector3
{
	const static Vector3 Zero;
	const static Vector3 One;
	const static Vector3 Up;
	const static Vector3 Down;
	const static Vector3 Left;
	const static Vector3 Right;
	const static Vector3 Forward;
	const static Vector3 Back;

	double x = 0.0;
	double y = 0.0;
	double z = 0.0;

	Vector3() = default;
	Vector3(double val)
		: x(val), y(val), z(val) { }
	Vector3(double x, double y, double z)
		: x(x), y(y), z(z) { }
	Vector3(const Vector3& other)
		: x(other.x), y(other.y), z(other.z) { }

	void Normalise()
	{
		double magnitude = Magnitude();
		if (magnitude != 0.0)
		{
			x /= magnitude;
			y /= magnitude;
			z /= magnitude;
		}
	}

	Vector3 GetNormalised()
	{
		double magnitude = Magnitude();
		Vector3 result = (magnitude != 0.0) ? (*this / magnitude) : Vector3::Zero;
		return result;
	}

	static double DistanceSqr(const Vector3& a, const Vector3& b)
	{
		double diffX = a.x - b.x;
		double diffY = a.y - b.y;
		double diffZ = a.z - b.z;
		return diffX * diffX + diffY * diffY + diffZ * diffZ;
	}

	static double Distance(const Vector3& a, const Vector3& b) { return Math::Sqrt(DistanceSqr(a, b)); }
	double MagnitudeSqr() const { return (x * x + y * y + z * z); }
	double Magnitude() const { return Math::Sqrt(MagnitudeSqr()); }
	static double Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
	static Vector3 Cross(const Vector3& a, const Vector3& b) { return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }

#pragma region Operator Overloads

	Vector3 operator=(const Vector3& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	Vector3 operator/(double val)
	{
		return Vector3(x / val, y / val, z / val);
	}

	Vector3 operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3 operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3 operator*=(double val)
	{
		x *= val;
		y *= val;
		z *= val;
		return *this;
	}

	Vector3 operator*=(Vector3 other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	Vector3 operator/=(double val)
	{
		x /= val;
		y /= val;
		z /= val;
		return *this;
	}

	Vector3 operator++()
	{
		x++;
		y++;
		z++;
		return *this;
	}

	Vector3 operator--()
	{
		x--;
		y--;
		z--;
		return *this;
	}

	Vector3 operator++(int)
	{
		Vector3 result(*this);
		++* this;
		return result;
	}

	double& operator[](int index)
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 3);
		return (&x)[index];
	}

	const double& operator[](int index) const
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 3);
		return (&x)[index];
	}

	bool operator==(const Vector3& other)
	{
		return (this[0] == other[0]) && (this[1] == other[1] && (this[2] == other[2]));
	}

	bool operator!=(const Vector3& other)
	{
		return !(*this == other);
	}

#pragma endregion
};

Vector3 operator+(const Vector3& a, const Vector3& b);
Vector3 operator-(const Vector3& a, const Vector3& b);
Vector3 operator*(const Vector3& a, const Vector3& b);
Vector3 operator*(const Vector3& vec, double scalar);