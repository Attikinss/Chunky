#include "Vector4f.h"

Vector4f const Vector4f::Zero	 = {  0.0f,  0.0f,  0.0f,  0.0f };
Vector4f const Vector4f::One	 = {  1.0f,  1.0f,  1.0f,  1.0f };
Vector4f const Vector4f::Up		 = {  0.0f,  1.0f,  0.0f,  0.0f };
Vector4f const Vector4f::Down	 = {  0.0f, -1.0f,  0.0f,  0.0f };
Vector4f const Vector4f::Left	 = { -1.0f,  0.0f,  0.0f,  0.0f };
Vector4f const Vector4f::Right	 = {  1.0f,  0.0f,  0.0f,  0.0f };
Vector4f const Vector4f::Forward = {  0.0f,  0.0f,  1.0f,  0.0f };
Vector4f const Vector4f::Back	 = {  0.0f,  0.0f, -1.0f,  0.0f };

Vector4f operator+(const Vector4f& a, const Vector4f& b)
{
	return Vector4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

Vector4f operator-(const Vector4f& a, const Vector4f& b)
{
	return Vector4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

Vector4f operator*(const Vector4f& a, const Vector4f& b)
{
	return Vector4f(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

Vector4f operator*(const Vector4f& vec, float scalar)
{
	return Vector4f(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
}