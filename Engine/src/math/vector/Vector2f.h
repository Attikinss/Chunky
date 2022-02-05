#pragma once
#include "math/Math.h"

struct Vector2f
{
	const static Vector2f Zero;
	const static Vector2f One;
	const static Vector2f Left;
	const static Vector2f Right;
	const static Vector2f Up;
	const static Vector2f Down;

	float x = 0.0;
	float y = 0.0;

	Vector2f() = default;
	Vector2f(float val)
		: x(val), y(val) { }
	Vector2f(float x, float y)
		: x(x), y(y) { }
	Vector2f(const Vector2f & other)
		: x(other.x), y(other.y) { }

	void Normalise()
	{
		float magnitude = Magnitude();
		if (magnitude != 0.0f)
		{
			x /= magnitude;
			y /= magnitude;
		}
	}

	Vector2f GetNormalised()
	{
		float magnitude = Magnitude();
		Vector2f result = (magnitude != 0.0f) ? (*this / magnitude) : Vector2f::Zero;
		return result;
	}

	static float DistanceSqr(const Vector2f& a, const Vector2f& b)
	{
		float diffX = a.x - b.x;
		float diffY = a.y - b.y;
		return diffX * diffX + diffY * diffY;
	}

	static float Distance(const Vector2f& a, const Vector2f& b) { return (float)Math::Sqrt(DistanceSqr(a, b)); }
	float MagnitudeSqr() const { return (x * x + y * y); }
	float Magnitude() const { return (float)Math::Sqrt(MagnitudeSqr()); }
	static float Dot(const Vector2f& a, const Vector2f& b) { return a.x * b.x + a.y * b.y; }

#pragma region Operator Overloads

	Vector2f operator=(const Vector2f& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	Vector2f operator/(float val)
	{
		return Vector2f(x / val, y / val);
	}

	Vector2f operator+=(const Vector2f& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2f operator-=(const Vector2f& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2f operator*=(float val)
	{
		x *= val;
		y *= val;
		return *this;
	}

	Vector2f operator*=(Vector2f other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Vector2f operator/=(float val)
	{
		x /= val;
		y /= val;
		return *this;
	}

	Vector2f operator++()
	{
		x++;
		y++;
		return *this;
	}

	Vector2f operator--()
	{
		x--;
		y--;
		return *this;
	}

	Vector2f operator++(int)
	{
		Vector2f result(*this);
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

	bool operator==(const Vector2f& other)
	{
		return (this[0] == other[0]) && (this[1] == other[1]);
	}

	bool operator!=(const Vector2f& other)
	{
		return !(*this == other);
	}

#pragma endregion
};

Vector2f operator+(const Vector2f& a, const Vector2f& b);
Vector2f operator-(const Vector2f& a, const Vector2f& b);
Vector2f operator*(const Vector2f& a, const Vector2f& b);
Vector2f operator*(const Vector2f& vec, float scalar);