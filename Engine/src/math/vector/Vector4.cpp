#include "Vector4.h"

Vector4 const Vector4::Zero	   = {  0.0,  0.0,  0.0,  0.0 };
Vector4 const Vector4::One	   = {  1.0,  1.0,  1.0,  1.0 };
Vector4 const Vector4::Up	   = {  0.0,  1.0,  0.0,  0.0 };
Vector4 const Vector4::Down	   = {  0.0, -1.0,  0.0,  0.0 };
Vector4 const Vector4::Left	   = { -1.0,  0.0,  0.0,  0.0 };
Vector4 const Vector4::Right   = {  1.0,  0.0,  0.0,  0.0 };
Vector4 const Vector4::Forward = {  0.0,  0.0,  1.0,  0.0 };
Vector4 const Vector4::Back	   = {  0.0,  0.0, -1.0,  0.0 };

Vector4 operator+(const Vector4& a, const Vector4& b)
{
	return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

Vector4 operator-(const Vector4& a, const Vector4& b)
{
	return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

Vector4 operator*(const Vector4& a, const Vector4& b)
{
	return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

Vector4 operator*(const Vector4& vec, double scalar)
{
	return Vector4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
}