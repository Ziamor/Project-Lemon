#pragma once
#include <vector>
#include <math.h>
class PerlinNoise
{
public:
	PerlinNoise(); 
	PerlinNoise(int seed);
	PerlinNoise( int seed, double persistence, int Number_Of_Octaves);
	~PerlinNoise();
	std::vector<double> PerlinNoise::getVecterPerlinNoise();
	double PerlinNoise::getPerlinNoise(double x, double y, double detail);
	
private:
	std::vector<double> perlinNoise;
	double PerlinNoise::noise(double x, double y);
	double PerlinNoise::smooth_noise(double x, double y);
	double PerlinNoise::interpolated_noise(double x, double y);
	double PerlinNoise::Cosine_Interpolate(double a, double b, double x);
	int seed, Number_Of_Octaves;
	double persistence;
};

