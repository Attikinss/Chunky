#pragma once
#include "math/Math.h"

struct Vector2
{
	const static Vector2 Zero;
	const static Vector2 One;
	const static Vector2 Left;
	const static Vector2 Right;
	const static Vector2 Up;
	const static Vector2 Down;

	double x = 0.0;
	double y = 0.0;

	Vector2() = default;
	Vector2(double val)
		: x(val), y(val) { }
	Vector2(double x, double y)
		: x(x), y(y) { }
	Vector2(const Vector2 & other)
		: x(other.x), y(other.y) { }

	void Normalise()
	{
		double magnitude = Magnitude();
		if (magnitude != 0.0)
		{
			x /= magnitude;
			y /= magnitude;
		}
	}

	Vector2 GetNormalised()
	{
		double magnitude = Magnitude();
		Vector2 result = (magnitude != 0.0) ? (*this / magnitude) : Vector2::Zero;
		return result;
	}

	static double DistanceSqr(const Vector2& a, const Vector2& b)
	{
		double diffX = a.x - b.x;
		double diffY = a.y - b.y;
		return diffX * diffX + diffY * diffY;
	}

	static double Distance(const Vector2& a, const Vector2& b) { return Math::Sqrt(DistanceSqr(a, b)); }
	double MagnitudeSqr() const { return (x * x + y * y); }
	double Magnitude() const { return Math::Sqrt(MagnitudeSqr()); }
	static double Dot(const Vector2& a, const Vector2& b) { return a.x * b.x + a.y * b.y; }

#pragma region Operator Overloads

	Vector2 operator=(const Vector2& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	Vector2 operator/(double val)
	{
		return Vector2(x / val, y / val);
	}

	Vector2 operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2 operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2 operator*=(double val)
	{
		x *= val;
		y *= val;
		return *this;
	}

	Vector2 operator*=(Vector2 other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Vector2 operator/=(double val)
	{
		x /= val;
		y /= val;
		return *this;
	}

	Vector2 operator++()
	{
		x++;
		y++;
		return *this;
	}

	Vector2 operator--()
	{
		x--;
		y--;
		return *this;
	}

	Vector2 operator++(int)
	{
		Vector2 result(*this);
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

	bool operator==(const Vector2& other)
	{
		return (this[0] == other[0]) && (this[1] == other[1]);
	}

	bool operator!=(const Vector2& other)
	{
		return !(*this == other);
	}

#pragma endregion
};

Vector2 operator+(const Vector2& a, const Vector2& b);
Vector2 operator-(const Vector2& a, const Vector2& b);
Vector2 operator*(const Vector2& a, const Vector2& b);
Vector2 operator*(const Vector2& vec, double scalar);