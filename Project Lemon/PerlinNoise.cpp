#include "PerlinNoise.h"


PerlinNoise::PerlinNoise() : seed(0), persistence(0), Number_Of_Octaves(0)
{
}

PerlinNoise::PerlinNoise(int seed) : seed(seed), persistence(0.25), Number_Of_Octaves(5)
{
}

PerlinNoise::PerlinNoise(int seed, double persistence, int Number_Of_Octaves) : seed(seed), persistence(persistence), Number_Of_Octaves(Number_Of_Octaves)
{

}

PerlinNoise::~PerlinNoise()
{
}

//TODO fix extreme numbers ///*new note* I think I fixed it already :/
double PerlinNoise::getPerlinNoise(double x, double y, double detail)
{
	double total = 0;
	int n = Number_Of_Octaves - 1;
	for (int i = 0; i < n; i++)
	{
		double frequency = pow(2, i);
		double amplitude = pow(persistence, i);

		total = total + interpolated_noise(x * frequency / detail, y * frequency / detail) * amplitude;
	}
	if (total < -1.0)
		total = -1.0;
	else if (total > 1.0)
		total = 1.0;
	return total;
}

double PerlinNoise::noise(double x, double y)
{
	int n = (int)(x + y * seed);
	n = (n << 13) ^ n;
	return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double PerlinNoise::smooth_noise(double x, double y)
{
	double corners = (noise(x - 1, y - 1) + noise(x + 1, y - 1) + noise(x - 1, y + 1) + noise(x + 1, y + 1)) / 16;
	double sides = (noise(x - 1, y) + noise(x + 1, y) + noise(x, y - 1) + noise(x, y + 1)) / 8;
	double center = noise(x, y) / 4;

	return corners + sides + center;
}

double PerlinNoise::interpolated_noise(double x, double y)
{
	int integer_X = (int)x;
	double fractional_X = x - integer_X;

	int integer_Y = (int)y;
	double fractional_Y = y - integer_Y;

	double v1 = smooth_noise(integer_X, integer_Y);
	double v2 = smooth_noise(integer_X + 1, integer_Y);
	double v3 = smooth_noise(integer_X, integer_Y + 1);
	double v4 = smooth_noise(integer_X + 1, integer_Y + 1);

	double i1 = Cosine_Interpolate(v1, v2, fractional_X);
	double i2 = Cosine_Interpolate(v3, v4, fractional_X);

	return Cosine_Interpolate(i1, i2, fractional_Y);

}

double PerlinNoise::Cosine_Interpolate(double a, double b, double x)
{
	double ft = x * 3.1415927;
	double f = (1 - cos(ft)) * .5;

	return  a*(1 - f) + b*f;
}

