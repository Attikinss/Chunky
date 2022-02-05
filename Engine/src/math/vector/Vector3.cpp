#include "Vector3.h"

Vector3 const Vector3::Zero	   = {  0.0,  0.0,  0.0 };
Vector3 const Vector3::One	   = {  1.0,  1.0,  1.0 };
Vector3 const Vector3::Up	   = {  0.0,  1.0,  0.0 };
Vector3 const Vector3::Down	   = {  0.0, -1.0,  0.0 };
Vector3 const Vector3::Left	   = { -1.0,  0.0,  0.0 };
Vector3 const Vector3::Right   = {  1.0,  0.0,  0.0 };
Vector3 const Vector3::Forward = {  0.0,  0.0,  1.0 };
Vector3 const Vector3::Back	   = {  0.0,  0.0, -1.0 };

Vector3 operator+(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3 operator-(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector3 operator*(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector3 operator*(const Vector3& vec, double scalar)
{
	return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}