#include <iostream>
#include <vector>
#include "Node.h"
#include "Network.h"

int main()
{
	phi::Network newNetwork(5, { 10,100,5,50,10 });
	for (signed short int layer = 0; layer < newNetwork.layers; ++layer)
	{
		for (signed int node = 0; node < newNetwork.nodes[layer]; ++node)
		{
			newNetwork.net[layer][node].addKHCords({ -1220, 10, 0, 5, 5, 10, 10, 20, 50, 100, 1220, 1, 99999, 99999 });
		}
	}
	vector<float> temp;
	for (int i = 0; i < newNetwork.nodes[0]; ++i)
	{
		temp.push_back(rand() % 5000);
	}
	newNetwork.calculate(temp);
	for (int layer = 1; layer < newNetwork.layers; ++layer)
	{
		for (int node = 0; node < newNetwork.nodes[layer]; ++node)
		{
			for (int connection = 0; connection < newNetwork.nodes[layer-1]; ++connection)
			{
				float output = newNetwork.net[layer][node].value;
				//std::cout << output << "\n\n";
			}
		}
	}
	cout << "something";
	int something;
	cin >> something;
}
