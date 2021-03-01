#pragma once
#include <random>
#include <vector>

using namespace std;

class randomClass
{
public:

	int variation = 0;
	vector<float> random = { };
	signed int rdmIndex = 0;

	randomClass( int variationAmt, signed int layers, vector<signed int> nodes, signed int iterationAmt)
	{
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(0-variationAmt, variationAmt);
		int dice_roll = distribution(generator);  // generates number in the range 1..6 

		for (signed int layer = 0; layer < layers; layer++)
		{
			for (int i = 0; i < nodes[layer] * 6; i++)
			{
				random.push_back(distribution(generator));
			}
		}
		for (signed int i = 0; i < iterationAmt; i++)
		{
			for (signed int node = 0; node < nodes[0]; node++)
			{
				random.push_back(distribution(generator));
			}
		}
		for (int i = 0; i < 100; i++)
		{
			random.push_back(distribution(generator));
		}
	}

	float rdmGenerator()
	{
		float something = random[rdmIndex];
		rdmIndex++;
		return something;
	}
};

