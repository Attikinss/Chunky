#include "Vector2.h"

Vector2 const Vector2::Zero	 = {  0.0,  0.0 };
Vector2 const Vector2::One	 = {  1.0,  1.0 };
Vector2 const Vector2::Left	 = { -1.0,  0.0 };
Vector2 const Vector2::Right = {  1.0,  0.0 };
Vector2 const Vector2::Up	 = {  0.0,  1.0 };
Vector2 const Vector2::Down	 = {  0.0, -1.0 };

Vector2 operator+(const Vector2& a, const Vector2& b)
{
	return Vector2(a.x + b.x, a.y + b.y);
}

Vector2 operator-(const Vector2& a, const Vector2& b)
{
	return Vector2(a.x - b.x, a.y - b.y);
}

Vector2 operator*(const Vector2& a, const Vector2& b)
{
	return Vector2(a.x * b.x, a.y * b.y);
}

Vector2 operator*(const Vector2& vec, double scalar)
{
	return Vector2(vec.x * scalar, vec.y * scalar);
}
