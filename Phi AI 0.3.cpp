#include <iostream>
#include <vector>
#include "Node.h"
#include "Network.h"
#include <ctime>
#include <random>

int globalvaribale = 1000;

std::default_random_engine generator;													// for random weights
std::uniform_int_distribution<int> distribution(-globalvaribale, globalvaribale);	//
float randomFloat()
{
	float something = distribution(generator);
	return something;
}

void testerFunction()
{
	cout << randomFloat();
	cout << randomFloat();

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
	double output = 500;
	for (signed int i = 1; i < input_Layers; i++)
	{
		output += (input_Nodes[i] / 724 * input_Nodes[i - 1] / 724);
	}
	cout << "approx mem usage: " << output << "mb " << "(" << output / 1024 << "gb) \n";
	cout << "how many iterations?";
	signed int iterationAmt;
	cin >> iterationAmt;
	cout << "Initializing Net . . . \n";
	int timeStart = time(nullptr);
	//phi::Network somethingNetwork(input_Layers, input_Nodes);
	phi::Network newNetwork(input_Layers, input_Nodes);
	for (signed short int layer = 0; layer < newNetwork.layers; ++layer)
	{
		for (signed int node = 0; node < newNetwork.nodes[layer]; ++node)
		{
			newNetwork.net[layer][node].addKHCords({ randomFloat(), randomFloat(), randomFloat(), randomFloat(), randomFloat(), randomFloat() });
		}
	}
	vector<float> temp;

	cout << "Net finished in " << time(nullptr) - timeStart << " seconds. \n";
	timeStart = time(nullptr);
	cout << "Calculating x10 . . . \n";

	for (int i = 0; i < iterationAmt; i++)
	{
		temp = {  };
		for (int i0 = 0; i0 < newNetwork.nodes[0]; ++i0)
		{
			temp.push_back(randomFloat());
			float temp0 = temp[i0];
			cout << temp0 << ", ";
		}
		newNetwork.calculate(temp);
		cout << "\n = ";
		for (int node = 0; node < newNetwork.nodes[input_Layers - 1]; ++node)
		{
			float output = newNetwork.net[input_Layers - 1][node].value;
			cout << output << ", ";
		}
	}

	cout << "Finished in " << time(nullptr) - timeStart << " seconds. \n";
	for (int node = 0; node < newNetwork.nodes[input_Layers - 1]; ++node)
	{
		float output = newNetwork.net[input_Layers - 1][node].value;
		//std::cout << output << "\n";
	}
	cout << "done \n";
}

int main()
{
	for (bool thing = false; thing == false; thing = false)
	{
		testerFunction();
		std::cout << "would you like to do another? (y/n) \n";
		char input;
		cin >> input;
		thing = input == 'y';
	}
}
