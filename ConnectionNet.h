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
				for (int connection = 0; connection < nodesAtLayers[layer - 1]; connection++)
				{
				}
			}
		}
	}

	

private:
};
