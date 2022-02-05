#pragma once
#include "math/Math.h"

struct Vector4f
{
	const static Vector4f Zero;
	const static Vector4f One;
	const static Vector4f Up;
	const static Vector4f Down;
	const static Vector4f Left;
	const static Vector4f Right;
	const static Vector4f Forward;
	const static Vector4f Back;

	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
	float w = 0.0;

	Vector4f() = default;
	Vector4f(float val)
		: x(val), y(val), z(val), w(val) { }
	Vector4f(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w) { }
	Vector4f(const Vector4f& other)
		: x(other.x), y(other.y), z(other.z), w(other.w) { }

	void Normalise()
	{
		float magnitude = Magnitude();
		if (magnitude != 0.0f)
		{
			x /= magnitude;
			y /= magnitude;
			z /= magnitude;
			w /= magnitude;
		}
	}

	Vector4f GetNormalised()
	{
		float magnitude = Magnitude();
		Vector4f result = (magnitude != 0.0f) ? (*this / magnitude) : Vector4f::Zero;
		return result;
	}

	static float DistanceSqr(const Vector4f& a, const Vector4f& b)
	{
		float diffX = a.x - b.x;
		float diffY = a.y - b.y;
		float diffZ = a.z - b.z;
		return diffX * diffX + diffY * diffY + diffZ * diffZ;
	}

	static float Distance(const Vector4f& a, const Vector4f& b) { return (float)Math::Sqrt(DistanceSqr(a, b)); }
	float MagnitudeSqr() const { return (x * x + y * y + z * z + w * w); }
	float Magnitude() const { return (float)Math::Sqrt(MagnitudeSqr()); }
	static float Dot(const Vector4f& a, const Vector4f& b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

#pragma region Operator Overloads

	Vector4f operator=(const Vector4f& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}

	Vector4f operator/(float val)
	{
		return Vector4f(x / val, y / val, z / val, w / val);
	}

	Vector4f operator+=(const Vector4f& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	Vector4f operator-=(const Vector4f& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	Vector4f operator*=(float val)
	{
		x *= val;
		y *= val;
		z *= val;
		w *= val;
		return *this;
	}

	Vector4f operator*=(Vector4f other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	Vector4f operator/=(float val)
	{
		x /= val;
		y /= val;
		z /= val;
		w /= val;
		return *this;
	}

	Vector4f operator++()
	{
		x++;
		y++;
		z++;
		w++;
		return *this;
	}

	Vector4f operator--()
	{
		x--;
		y--;
		z--;
		w--;
		return *this;
	}

	Vector4f operator++(int)
	{
		Vector4f result(*this);
		++* this;
		return result;
	}

	Vector4f operator--(int)
	{
		Vector4f result(*this);
		--* this;
		return result;
	}

	float& operator[](int index)
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 4);
		return (&x)[index];
	}

	const float& operator[](int index) const
	{
		// TODO: Add clamping or ASSERT(index >= 0 && index < 4);
		return (&x)[index];
	}

	bool operator==(const Vector4f& other)
	{
		float xResult = x - other.x;
		float yResult = y - other.y;
		float zResult = z - other.z;
		float wResult = w - other.w;

		return (Math::Abs(xResult) < Math::Epsilon && Math::Abs(yResult) < Math::Epsilon && Math::Abs(zResult) < Math::Epsilon && Math::Abs(wResult) < Math::Epsilon);
	}

	bool operator!=(const Vector4f& other)
	{
		return !(*this == other);
	}

#pragma endregion
};

Vector4f operator+(const Vector4f& a, const Vector4f& b);
Vector4f operator-(const Vector4f& a, const Vector4f& b);
Vector4f operator*(const Vector4f& a, const Vector4f& b);
Vector4f operator*(const Vector4f& vec, float scalar);