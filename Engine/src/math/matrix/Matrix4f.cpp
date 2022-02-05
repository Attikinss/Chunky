#include "Matrix4f.h"

Vector4f operator*(const Vector4f& vector, const Matrix4f& matrix)
{
	return Vector4f(
		matrix[0][0] * vector[0] + matrix[0][1] * vector[1] + matrix[0][2] * vector[2] + matrix[0][3] * vector[3],
		matrix[1][0] * vector[0] + matrix[1][1] * vector[1] + matrix[1][2] * vector[2] + matrix[1][3] * vector[3],
		matrix[2][0] * vector[0] + matrix[2][1] * vector[1] + matrix[2][2] * vector[2] + matrix[2][3] * vector[3],
		matrix[3][0] * vector[0] + matrix[3][1] * vector[1] + matrix[3][2] * vector[2] + matrix[3][3] * vector[3]);
}

Vector4f operator/(const Vector4f& vector, const Matrix4f& matrix)
{
	return vector * Matrix4f::Inverse(matrix);
}