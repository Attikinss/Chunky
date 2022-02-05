#pragma once
#include "math/Math.h"

struct Vector3f
{
	const static Vector3f Zero;
	const static Vector3f One;
	const static Vector3f Up;
	const static Vector3f Down;
	const static Vector3f Left;
	const static Vector3f Right;
	const static Vector3f Forward;
	const static Vector3f Back;

	float x = 0.0;
	float y = 0.0;
	float z = 0.0;

	Vector3f() = default;
	Vector3f(float val)
		: x(val), y(val), z(val) { }
	Vector3f(float x, float y, float z)
		: x(x), y(y), z(z) { }
	Vector3f(const Vector3f& other)
		: x(other.x), y(other.y), z(other.z) { }

	void Normalise()
	{
		float magnitude = Magnitude();
		if (magnitude != 0.0f)
		{
			x /= magnitude;
			y /= magnitude;
			z /= magnitude;
		}
	}

	Vector3f GetNormalised()
	{
		float magnitude = Magnitude();
		Vector3f result = (magnitude != 0.0f) ? (*this / magnitude) : Vector3f::Zero;
		return result;
	}

	static float DistanceSqr(const Vector3f& a, const Vector3f& b)
	{
		float diffX = a.x - b.x;
		float diffY = a.y - b.y;
		float diffZ = a.z - b.z;
		return diffX * diffX + diffY * diffY + diffZ * diffZ;
	}

	static float Distance(const Vector3f& a, const Vector3f& b) { return (float)Math::Sqrt(DistanceSqr(a, b)); }
	float MagnitudeSqr() const { return (x * x + y * y + z * z); }
	float Magnitude() const { return (float)Math::Sqrt(MagnitudeSqr()); }
	static float Dot(const Vector3f& a, const Vector3f& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
	static Vector3f Cross(const Vector3f& a, const Vector3f& b) { return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }

#pragma region Operator Overloads

	Vector3f operator=(const Vector3f& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	Vector3f operator/(float val)
	{
		return Vector3f(x / val, y / val, z / val);
	}

	Vector3f operator+=(const Vector3f& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3f operator-=(const Vector3f& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3f operator*=(float val)
	{
		x *= val;
		y *= val;
		z *= val;
		return *this;
	}

	Vector3f operator*=(Vector3f other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	Vector3f operator/=(float val)
	{
		x /= val;
		y /= val;
		z /= val;
		return *this;
	}

	Vector3f operator++()
	{
		x++;
		y++;
		z++;
		return *this;
	}

	Vector3f operator--()
	{
		x--;
		y--;
		z--;
		return *this;
	}

	Vector3f operator++(int)
	{
		Vector3f result(*this);
		++* this;
		return result;
	}

	float& operator[](int index)
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 3);
		return (&x)[index];
	}

	const float& operator[](int index) const
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 3);
		return (&x)[index];
	}

	bool operator==(const Vector3f& other)
	{
		return (this[0] == other[0]) && (this[1] == other[1] && (this[2] == other[2]));
	}

	bool operator!=(const Vector3f& other)
	{
		return !(*this == other);
	}

#pragma endregion
};

Vector3f operator+(const Vector3f& a, const Vector3f& b);
Vector3f operator-(const Vector3f& a, const Vector3f& b);
Vector3f operator*(const Vector3f& a, const Vector3f& b);
Vector3f operator*(const Vector3f& vec, float scalar);