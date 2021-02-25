#pragma once
#include <vector>

using namespace std;

namespace phi
{
	class CompressedNode
	{
		float value;
		float khList;
		float sted[4];
		vector<float> connectionWeights;
	};
}