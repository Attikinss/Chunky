#include "Vector3f.h"

Vector3f const Vector3f::Zero	 = {  0.0f,  0.0f,  0.0f };
Vector3f const Vector3f::One	 = {  1.0f,  1.0f,  1.0f };
Vector3f const Vector3f::Up		 = {  0.0f,  1.0f,  0.0f };
Vector3f const Vector3f::Down	 = {  0.0f, -1.0f,  0.0f };
Vector3f const Vector3f::Left	 = { -1.0f,  0.0f,  0.0f };
Vector3f const Vector3f::Right	 = {  1.0f,  0.0f,  0.0f };
Vector3f const Vector3f::Forward = {  0.0f,  0.0f,  1.0f };
Vector3f const Vector3f::Back	 = {  0.0f,  0.0f, -1.0f };

Vector3f operator+(const Vector3f& a, const Vector3f& b)
{
	return Vector3f(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3f operator-(const Vector3f& a, const Vector3f& b)
{
	return Vector3f(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector3f operator*(const Vector3f& a, const Vector3f& b)
{
	return Vector3f(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector3f operator*(const Vector3f& vec, float scalar)
{
	return Vector3f(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}