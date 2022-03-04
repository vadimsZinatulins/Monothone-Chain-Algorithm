#pragma once

#include <random>

class Random
{
public:
	Random(int seed);
	Random();
	~Random();

	int nextInt();
	int nextInt(int max);
	int nextInt(int min, int max);

	float nextFloat();
	float nextFloat(float max);
	float nextFloat(float min, float max);
private:
	std::mt19937 m_engine;
};
