#include "Vector2f.h"

Vector2f const Vector2f::Zero  = {  0.0f,  0.0f };
Vector2f const Vector2f::One   = {  1.0f,  1.0f };
Vector2f const Vector2f::Left  = { -1.0f,  0.0f };
Vector2f const Vector2f::Right = {  1.0f,  0.0f };
Vector2f const Vector2f::Up	   = {  0.0f,  1.0f };
Vector2f const Vector2f::Down  = {  0.0f, -1.0f };

Vector2f operator+(const Vector2f& a, const Vector2f& b)
{
	return Vector2f(a.x + b.x, a.y + b.y);
}

Vector2f operator-(const Vector2f& a, const Vector2f& b)
{
	return Vector2f(a.x - b.x, a.y - b.y);
}

Vector2f operator*(const Vector2f& a, const Vector2f& b)
{
	return Vector2f(a.x * b.x, a.y * b.y);
}

Vector2f operator*(const Vector2f& vec, float scalar)
{
	return Vector2f(vec.x * scalar, vec.y * scalar);
}
