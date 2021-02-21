#pragma once
#include <vector>
#include <iostream>

using namespace std;
class ConnectionNet
{
public:
	vector<vector<vector<int>>> net;
	int layers;
	vector<int> nodesAtLayers;

	ConnectionNet(int Layers, vector<int> NodesAtLayers)
	{
		layers = Layers;
		nodesAtLayers = NodesAtLayers;
		for (int layer = 0; layer < layers; layer++)
		{
			net.push_back({ });
			for (int node = 0; node < nodesAtLayers[layer]; node++)
			{
				net[layer].push_back({ });
				for (int connection = 0; connection < nodesAtLayers[layer-1]; connection++)
				{

				}
			}
		}
	}

	class BellNet
	{
		vector<vector<vector<int>>> xCords;
		vector<vector<vector<int>>> yCords;

		void theFunctionThing(int x1, int y1)
		{

			int h;
			int k;
			int y2 = y2;
			signed int dataPointAmt = 0;
			// baseh = 2 * y2 / x2
			// basek = x2 / 2

			bool highLow = y1 > 2 * y2 * x1 / (2 * x2); // true = high

			if (y1 == 2 * y2 * x1 / (2 * x2))
			{
				h = 2 * y2 / x2;
				k = x2 / 2;
				return;
			}

			if (dataPointAmt == 3)
			{
				if (highLow == false)
				{
					k = y2 * x1 ^ 2 / (y1 * x2);
				}
				else
				{
					k = (x2 * y1 + x2 * x1 * (x1 / x2 - 2)) / (y1 - y2);
				}
			}
		}
		int eval(int x, int h, int k, int x2, int x1, int y2)
		{
			if (x <= k)
			{
				return h * x ^ 2 / (2 * k);
			}
			else
			{
				return h * (x - k / 2 - (x - k) ^ 2 / (2 * (x2 - k)));
			}
		}
	};


private:

};

