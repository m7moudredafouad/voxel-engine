#include "Perlin.h"


double PerlinNoise::fade(double t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::lerp(double t, double a, double b) {
	return a + t * (b - a);
}

double PerlinNoise::grad(int hash, double x, double y, double z) {
	int h = hash & 15;
	// Convert lower 4 bits of hash into 12 gradient directions
	double u = h < 8 ? x : y,
		v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

PerlinNoise::PerlinNoise(unsigned int seed) {
	this->p.resize(256);
	int indx = 0;
	// Fill p with values from 0 to 255
	std::generate(this->p.begin(), this->p.end(), [&indx] {return indx++; });

	// Initialize a random engine with seed
	std::default_random_engine engine(seed);

	// Suffle  using the above random engine
	std::shuffle(this->p.begin(), this->p.end(), engine);

	// Duplicate the permutation vector
	this->p.insert(this->p.end(), this->p.begin(), this->p.end());
}

double PerlinNoise::noise(double x, double y, double z) {
	// Find the unit cube that contains the point
	int X = (int)floor(x) & 255;
	int Y = (int)floor(y) & 255;
	int Z = (int)floor(z) & 255;

	// Find relative x, y,z of point in cube
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);

	// Compute fade curves for each of x, y, z
	double u = fade(x);
	double v = fade(y);
	double w = fade(z);

	// Hash coordinates of the 8 cube corners
	int A = this->p[X] + Y;
	int AA = this->p[A] + Z;
	int AB = this->p[A + 1] + Z;
	int B = this->p[X + 1] + Y;
	int BA = this->p[B] + Z;
	int BB = this->p[B + 1] + Z;

	// Add blended results from 8 corners of cube
	double res = lerp(w,
					lerp(v, 
						lerp(u,
							grad(this->p[AA], x, y, z),
							grad(this->p[BA], x - 1, y, z)
						),
						lerp(u,
							grad(this->p[AB], x, y - 1, z),
							grad(this->p[BB], x - 1, y - 1, z)
						)
					),
					lerp(v, 
						lerp(u, grad(this->p[AA + 1], x, y, z - 1), grad(this->p[BA + 1], x - 1, y, z - 1)),
						lerp(u, grad(this->p[AB + 1], x, y - 1, z - 1), grad(this->p[BB + 1], x - 1, y - 1, z - 1))
					)
				);
	return (res + 1.0) / 2.0;
}

