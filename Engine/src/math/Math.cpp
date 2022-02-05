#include "Math.h"
#include <numeric>

const double Math::Epsilon = 1.0e-7;
const double Math::PI = 3.1415926535897932;
const double Math::Rad2Deg = 57.2957795130823216;
const double Math::Deg2Rad = 0.0174532925199433;
const double Math::Infinity = std::numeric_limits<double>::infinity();
const double Math::NegInfinity = -std::numeric_limits<double>::infinity();
const double Math::NaN = -std::numeric_limits<double>::quiet_NaN();

double Math::Abs(double x)
{
	return abs(x);
}

double Math::Acos(double x)
{
	return acos(x);
}

double Math::Asin(double x)
{
	return asin(x);
}

double Math::Atan(double x)
{
	return atan(x);
}

double Math::Atan2(double y, double x)
{
	return atan2(y, x);
}

double Math::Ceil(double x)
{
	return ceil(x);
}

int Math::CeilToInt(double x)
{
	return (int)ceil(x);
}

double Math::Clamp(double x, double min, double max)
{
	return x < min ? min : (x > max ? max : x);
}

double Math::Clamp01(double x)
{
	return Clamp(x, 0.0, 1.0);
}

double Math::Cos(double radians)
{
	return cos(radians);
}

double Math::Exp(double x)
{
	return exp(x);
}

double Math::Exp2(double x)
{
	return exp(x);
}

double Math::Fact(int n)
{
	return n > 1 ? n * Fact(n - 1) : 1;
}

double Math::Floor(double x)
{
	return floor(x);
}

int Math::FloorToInt(double x)
{
	return (int)floor(x);
}

double Math::InverseLerp(double a, double b, double t)
{
	return (t - a) / (b - a);
}

bool Math::IsPowerOfTwo(int x)
{
	return (x & (x - 1)) == 0;
}

double Math::Lerp(double a, double b, double t)
{
	return a + t * (b - a);
}

double Math::Log(double x)
{
	return log(x);
}

double Math::Log10(double x)
{
	return log10(x);
}

double Math::Min(double a, double b)
{
	return a < b ? a : b;
}

double Math::Max(double a, double b)
{
	return a > b ? a : b;
}

double Math::Round(double x)
{
	return round(x);
}

double Math::RoundTo(double x, int decimalPlaces)
{
	const double mult = pow(10, decimalPlaces);
	return round(x * mult) / mult;
}

int Math::RoundToInt(double x)
{
	return (int)round(x);
}

double Math::Pow(double x, int power)
{
	return pow(x, power);
}

double Math::Sin(double radians)
{
	return sin(radians);
}

double Math::Sqrt(double x)
{
	return sqrt(x);
}

double Math::Tan(double x)
{
	return tan(x);
}
