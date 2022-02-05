#pragma once
#include "math/Math.h"

struct Vector4
{
	const static Vector4 Zero;
	const static Vector4 One;
	const static Vector4 Up;
	const static Vector4 Down;
	const static Vector4 Left;
	const static Vector4 Right;
	const static Vector4 Forward;
	const static Vector4 Back;

	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	double w = 0.0;

	Vector4() = default;
	Vector4(double val)
		: x(val), y(val), z(val), w(val) { }
	Vector4(double x, double y, double z, double w)
		: x(x), y(y), z(z), w(w) { }
	Vector4(const Vector4& other)
		: x(other.x), y(other.y), z(other.z), w(other.w) { }

	void Normalise()
	{
		double magnitude = Magnitude();
		if (magnitude != 0.0)
		{
			x /= magnitude;
			y /= magnitude;
			z /= magnitude;
			w /= magnitude;
		}
	}

	Vector4 GetNormalised()
	{
		double magnitude = Magnitude();
		Vector4 result = (magnitude != 0.0) ? (*this / magnitude) : Vector4::Zero;
		return result;
	}

	static double DistanceSqr(const Vector4& a, const Vector4& b)
	{
		double diffX = a.x - b.x;
		double diffY = a.y - b.y;
		double diffZ = a.z - b.z;
		return diffX * diffX + diffY * diffY + diffZ * diffZ;
	}

	static double Distance(const Vector4& a, const Vector4& b) { return Math::Sqrt(DistanceSqr(a, b)); }
	double MagnitudeSqr() const { return (x * x + y * y + z * z + w * w); }
	double Magnitude() const { return Math::Sqrt(MagnitudeSqr()); }
	static double Dot(const Vector4& a, const Vector4& b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

#pragma region Operator Overloads

	Vector4 operator=(const Vector4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}

	Vector4 operator/(double val)
	{
		return Vector4(x / val, y / val, z / val, w / val);
	}

	Vector4 operator+=(const Vector4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	Vector4 operator-=(const Vector4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	Vector4 operator*=(double val)
	{
		x *= val;
		y *= val;
		z *= val;
		w *= val;
		return *this;
	}

	Vector4 operator*=(Vector4 other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	Vector4 operator/=(double val)
	{
		x /= val;
		y /= val;
		z /= val;
		w /= val;
		return *this;
	}

	Vector4 operator++()
	{
		x++;
		y++;
		z++;
		w++;
		return *this;
	}

	Vector4 operator--()
	{
		x--;
		y--;
		z--;
		w--;
		return *this;
	}

	Vector4 operator++(int)
	{
		Vector4 result(*this);
		++* this;
		return result;
	}

	Vector4 operator--(int)
	{
		Vector4 result(*this);
		--* this;
		return result;
	}

	double& operator[](int index)
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 4);
		return (&x)[index];
	}

	const double& operator[](int index) const
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 4);
		return (&x)[index];
	}

	bool operator==(const Vector4& other)
	{
		double xResult = x - other.x;
		double yResult = y - other.y;
		double zResult = z - other.z;
		double wResult = w - other.w;

		return (Math::Abs(xResult) < Math::Epsilon && Math::Abs(yResult) < Math::Epsilon && Math::Abs(zResult) < Math::Epsilon && Math::Abs(wResult) < Math::Epsilon);
	}

	bool operator!=(const Vector4& other)
	{
		return !(*this == other);
	}

#pragma endregion
};

Vector4 operator+(const Vector4& a, const Vector4& b);
Vector4 operator-(const Vector4& a, const Vector4& b);
Vector4 operator*(const Vector4& a, const Vector4& b);
Vector4 operator*(const Vector4& vec, double scalar);