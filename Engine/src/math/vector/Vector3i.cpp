#include "Vector3i.h"

Vector3i const Vector3i::Zero	 = {  0,  0,  0 };
Vector3i const Vector3i::One	 = {  1,  1,  1 };
Vector3i const Vector3i::Up		 = {  0,  1,  0 };
Vector3i const Vector3i::Down	 = {  0, -1,  0 };
Vector3i const Vector3i::Left	 = { -1,  0,  0 };
Vector3i const Vector3i::Right	 = {  1,  0,  0 };
Vector3i const Vector3i::Forward = {  0,  0,  1 };
Vector3i const Vector3i::Back	 = {  0,  0, -1 };

Vector3i operator+(const Vector3i& a, const Vector3i& b)
{
	return Vector3i(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3i operator-(const Vector3i& a, const Vector3i& b)
{
	return Vector3i(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector3i operator*(const Vector3i& a, const Vector3i& b)
{
	return Vector3i(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector3i operator*(const Vector3i& vec, int val)
{
	return Vector3i(vec.x * val, vec.y * val, vec.z * val);
}