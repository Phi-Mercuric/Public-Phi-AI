#include <iostream>
#include <vector>
#include "Node.h"
#include "Network.h"
#include <ctime>

int main()
{
	signed int input_Layers;
	vector<signed int> input_Nodes;
	cout << "How many layers do you wish to make? \n";
	cin >> input_Layers;
	for (int i = 0; i < input_Layers; i++)
	{
		cout << "How many nodes in layer " << i + 1 << " ? \n";
		signed int localInput;
		cin >> localInput;
		input_Nodes.push_back(localInput);
	}
	double output = input_Nodes[0] / 2600 + 200;
	for (int i = 1; i < input_Layers; i++)
	{
		output += (input_Nodes[i] * 100  + input_Nodes[i] * input_Nodes[i - 1]) / 400000;
	}
	cout << "approx mem usage: " << output << "mb " << "(" << output / 1024 << "gb) \n";
	cout << "Initializing Net . . . \n";
	int timeStart = time(nullptr);
	//phi::Network somethingNetwork(input_Layers, input_Nodes);
	phi::Network newNetwork(input_Layers, input_Nodes);
	for (signed short int layer = 0; layer < newNetwork.layers; ++layer)
	{
		for (signed int node = 0; node < newNetwork.nodes[layer]; ++node)
		{
			newNetwork.net[layer][node].addKHCords({ -9999, 9999, -1220, 10, 0, 5, 5, 10, 10, 20, 50, 100, 1220, 1, 99999, 99999 });
		}
	}
	vector<float> temp;
	for (int i = 0; i < newNetwork.nodes[0]; ++i)
	{
		temp.push_back(rand() % 50);
	}
	cout << "Net finished in" << time(nullptr) - timeStart << " seconds. \n";
	timeStart = time(nullptr);
	cout << "Calculating x10 . . . \n";
	newNetwork.calculate(temp);
	newNetwork.calculate(temp);
	newNetwork.calculate(temp);
	newNetwork.calculate(temp);
	newNetwork.calculate(temp);
	newNetwork.calculate(temp);
	newNetwork.calculate(temp);
	newNetwork.calculate(temp);
	newNetwork.calculate(temp);
	newNetwork.calculate(temp);
	newNetwork.calculate(temp);
	cout << "Finished in" << time(nullptr) - timeStart << " seconds. \n";
	for (int layer = 1; layer < newNetwork.layers; ++layer)
	{
		for (int node = 0; node < newNetwork.nodes[layer]; ++node)
		{
			for (int connection = 0; connection < newNetwork.nodes[layer - 1]; ++connection)
			{
				float output = newNetwork.net[layer][node].value;
				//std::cout << output << "\n\n";
			}
		}
	}
	cout << "done";
	int something;
	cin >> something;
}
