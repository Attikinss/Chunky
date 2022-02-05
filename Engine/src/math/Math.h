#pragma once

struct Math
{
	const static double Epsilon;
	const static double PI;
	const static double Rad2Deg;
	const static double Deg2Rad;
	const static double Infinity;
	const static double NegInfinity;
	const static double NaN;

	static double Abs(double x);
	static double Acos(double x);
	static double Asin(double x);
	static double Atan(double x);
	static double Atan2(double y, double x);
	static double Ceil(double x);
	static int CeilToInt(double x);
	static double Clamp(double x, double min, double max);
	static double Clamp01(double x);
	static double Cos(double radians);
	static double Exp(double x);
	static double Exp2(double x);
	static double Fact(int n);
	static double Floor(double x);
	static int FloorToInt(double x);
	static double InverseLerp(double a, double b, double t);
	static bool IsPowerOfTwo(int x);
	static double Lerp(double a, double b, double t);
	static double Log(double x);
	static double Log10(double x);
	static double Min(double a, double b);
	static double Max(double a, double b);
	static double Pow(double x, int power);
	static double Round(double x);
	static double RoundTo(double x, int decimalPlaces = 4);
	static int RoundToInt(double x);
	static double Sin(double radians);
	static double Sqrt(double x);
	static double Tan(double x);
};