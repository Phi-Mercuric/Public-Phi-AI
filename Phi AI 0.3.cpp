#include <iostream>
#include <vector>
#include "Node.h"
#include "Network.h"
#include <ctime>
#include <random>
#include "randomClass.h"
#include <chrono>
#include <iomanip>

using namespace std;

void calculateNetwork()
{
	unsigned int input_Layers;
	vector<unsigned int> input_Nodes;
	cout << "How many layers do you wish to make? \n";
	cin >> input_Layers;
	for (int i = 0; i < input_Layers; i++)
	{
		cout << "How many nodes in layer " << i + 1 << " ? \n";
		unsigned int localInput;
		cin >> localInput;
		input_Nodes.push_back(localInput);
	}
	double output = 500;
	for (unsigned int i = 1; i < input_Layers; i++)
	{
		output += (input_Nodes[i] / 724 * input_Nodes[i - 1] / 724);
	}
	cout << "approx mem usage: " << output << "mb " << "(" << output / 1024 << "gb) \n";
	cout << "how many iterations?";
	unsigned int iterationAmt;
	cin >> iterationAmt;
	cout << "what should the input variation be?";
	unsigned int inputVariation;
	cin >> inputVariation;
	cout << "would you like to see the inputs and outputs? (slows process) (y/n)";
	char inputLetter;
	cin >> inputLetter;
	bool visualIO = inputLetter == 'y';
	cout << "Initializing Net . . . \n";
	int timeStart = time(nullptr);
	//phi::Network somethingNetwork(input_Layers, input_Nodes);
	randomClass rdmClass(inputVariation, input_Layers, input_Nodes, iterationAmt);
	phi::Network newNetwork(input_Layers, input_Nodes);
	for (unsigned short int layer = 0; layer < newNetwork.layers; ++layer)
	{
		for (unsigned int node = 0; node < newNetwork.nodes[layer]; ++node)
		{
			newNetwork.net[layer][node].addKHCords({ rdmClass.rdmGenerator(), rdmClass.rdmGenerator(), rdmClass.rdmGenerator() });
		}
	}

	cout << "Net finished in " << time(nullptr) - timeStart << " seconds. \n";
	timeStart = time(nullptr);
	cout << "Calculating x" << iterationAmt << " . . . \n";

	for (int i = 0; i < iterationAmt; i++)
	{
		if (visualIO)
		{
			cout << "\n \n \n ---------Iteration "<< i << "---------- \n";
			cout << "Inputs: \n";
		}
		vector<float> tempInput;
		for (int i0 = 0; i0 < newNetwork.nodes[0]; i0++)
		{
			float temp0 = rdmClass.rdmGenerator();
			tempInput.push_back(temp0);
			if (visualIO)
			{
				cout << temp0 << ", ";
			}
		}
		newNetwork.calculate(tempInput);
		vector<float> BP_Input;
		if (visualIO)
		{
			cout << "\n \n Outputs: \n";
			for (int node = 0; node < newNetwork.nodes[input_Layers - 1]; ++node)
			{
				float something = newNetwork.net[input_Layers - 1][node].value + 0;
				BP_Input.push_back(newNetwork.net[input_Layers - 1][node].value);
				cout << something << ", ";
			}
		}
		else
		{
			for (int node = 0; node < newNetwork.nodes[input_Layers - 1]; ++node)
			{
				BP_Input.push_back(newNetwork.net[input_Layers - 1][node].value);
			}
		}
		newNetwork.backProp(BP_Input);
		if (newNetwork.net[1][0].xCordList.size() >= 3)
		{
			for (const auto& layer : newNetwork.net)
			{
				for (phi::Node node : layer)
				{
					node.pointGrouper(3, true);
					node.BCConstructor(true);
				}
			}
		}
		if (visualIO == false)
		{
			cout << "\n iteration #" << i + 1;
		}
	}

	cout << "\nFinished in " << time(nullptr) - timeStart << " seconds. \n";
	/*
		for (int node = 0; node < newNetwork.nodes[input_Layers - 1]; ++node)
		{
			float output = newNetwork.net[input_Layers - 1][node].value;
			cout << output << "\n";
		}*/
	cout << "done \n";
}

void DEBUG_calculateNetwork(bool debug = false, unsigned int debugNum = 0)
{
	if (debugNum > 0)
	{
		unsigned int input_Layers = debugNum;
		vector<unsigned int> input_Nodes;
		for (signed int i = 0; i < debugNum; i++)
		{
			input_Nodes.push_back(debugNum);
		}
		double output = 500;
		for (unsigned int i = 1; i < input_Layers; i++)
		{
			output += (input_Nodes[i] / 724 * input_Nodes[i - 1] / 724);
		}
		unsigned int iterationAmt = 5;
		unsigned int inputVariation = 10000;
		bool visualIO = true;
		cout << "Initializing Net . . . \n";
		int timeStart = time(nullptr);
		//phi::Network somethingNetwork(input_Layers, input_Nodes);
		randomClass rdmClass(inputVariation, input_Layers, input_Nodes, iterationAmt);
		phi::Network newNetwork(input_Layers, input_Nodes);
		for (unsigned short int layer = 0; layer < newNetwork.layers; ++layer)
		{
			for (unsigned int node = 0; node < newNetwork.nodes[layer]; ++node)
			{
				newNetwork.net[layer][node].addKHCords({ rdmClass.rdmGenerator(), rdmClass.rdmGenerator(), rdmClass.rdmGenerator() });
			}
		}

		cout << "Net finished in " << time(nullptr) - timeStart << " seconds. \n";
		timeStart = time(nullptr);
		cout << "Calculating x" << iterationAmt << " . . . \n";

		for (int i = 0; i < iterationAmt; i++)
		{
			if (visualIO)
			{
				cout << "\n \n \n ----------Iteration " << i << " ---------- \n";
				cout << "Inputs: \n";
			}
			vector<float> tempInput;
			for (int i0 = 0; i0 < newNetwork.nodes[0]; i0++)
			{
				float temp0 = rdmClass.rdmGenerator();
				tempInput.push_back(temp0);
				if (visualIO)
				{
					cout << temp0 << ", ";
				}
			}
			if (debug)
			{
				newNetwork.DEBUG_Calculate(tempInput);
				vector<float> BP_Input;
				cout << "\n \n Outputs: \n";
				for (int node = 0; node < newNetwork.nodes[input_Layers - 1]; ++node)
				{
					float something = newNetwork.net[input_Layers - 1][node].value / (1 + abs(newNetwork.net[input_Layers - 1][node].value));
					BP_Input.push_back(newNetwork.net[input_Layers - 1][node].value / (1 + abs(newNetwork.net[input_Layers - 1][node].value)));
					cout << something << ", ";
				}
				newNetwork.DEBUG_backProp(BP_Input, true);
				for (const auto& layer : newNetwork.net)
				{
					for (phi::Node node : layer)
					{
						cout << "\nfjkodips   " << node.xCordList.size();
						cout << "\nfjkodips   " << node.yCordList.size();
					}
				}
				if (newNetwork.net[1][0].xCordList.size() >= 3)
				{
					for (const auto& layer : newNetwork.net)
					{
						for (phi::Node node : layer)
						{
							node.pointGrouper(3, true);
							node.BCConstructor(true);
						}
					}
				}
			}
			else
			{
				newNetwork.calculate(tempInput);
				vector<float> BP_Input;
				if (visualIO)
				{
					cout << "\n \n Outputs: \n";
					for (int node = 0; node < newNetwork.nodes[input_Layers - 1]; ++node)
					{
						float something = newNetwork.net[input_Layers - 1][node].value + 0;
						BP_Input.push_back(newNetwork.net[input_Layers - 1][node].value);
						cout << something << ", ";
					}
				}
				else
				{
					for (int node = 0; node < newNetwork.nodes[input_Layers - 1]; ++node)
					{
						BP_Input.push_back(newNetwork.net[input_Layers - 1][node].value);
					}
				}
				newNetwork.backProp(BP_Input);
				if (newNetwork.net[1][0].xCordList.size() >= 3)
				{
					for (const auto& layer : newNetwork.net)
					{
						for (phi::Node node : layer)
						{
							node.pointGrouper(3, true);
							node.BCConstructor(true);
						}
					}
				}
			}
			if (visualIO == false)
			{
				cout << "\n iteration #" << i + 1;
			}
		}
	}
	unsigned int input_Layers;
	vector<unsigned int> input_Nodes;
	cout << "How many layers do you wish to make? \n";
	cin >> input_Layers;
	for (int i = 0; i < input_Layers; i++)
	{
		cout << "How many nodes in layer " << i + 1 << " ? \n";
		unsigned int localInput;
		cin >> localInput;
		input_Nodes.push_back(localInput);
	}
	double output = 500;
	for (unsigned int i = 1; i < input_Layers; i++)
	{
		output += (input_Nodes[i] / 724 * input_Nodes[i - 1] / 724);
	}
	cout << "approx mem usage: " << output << "mb " << "(" << output / 1024 << "gb) \n";
	cout << "how many iterations?";
	unsigned int iterationAmt;
	cin >> iterationAmt;
	cout << "what should the input variation be?";
	unsigned int inputVariation;
	cin >> inputVariation;
	cout << "would you like to see the inputs and outputs? (slows process) (y/n)";
	char inputLetter;
	cin >> inputLetter;
	bool visualIO = inputLetter == 'y';
	cout << "Initializing Net . . . \n";
	int timeStart = time(nullptr);
	//phi::Network somethingNetwork(input_Layers, input_Nodes);
	randomClass rdmClass(inputVariation, input_Layers, input_Nodes, iterationAmt);
	phi::Network newNetwork(input_Layers, input_Nodes);
	for (unsigned short int layer = 0; layer < newNetwork.layers; ++layer)
	{
		for (unsigned int node = 0; node < newNetwork.nodes[layer]; ++node)
		{
			newNetwork.net[layer][node].addKHCords({ rdmClass.rdmGenerator(), rdmClass.rdmGenerator(), rdmClass.rdmGenerator() });
		}
	}

	cout << "Net finished in " << time(nullptr) - timeStart << " seconds. \n";
	timeStart = time(nullptr);
	cout << "Calculating x" << iterationAmt << " . . . \n";

	for (int i = 0; i < iterationAmt; i++)
	{
		if (visualIO)
		{
			cout << "\n \n \n ----------Iteration " << i << " ---------- \n";
			cout << "Inputs: \n";
		}
		vector<float> tempInput;
		for (int i0 = 0; i0 < newNetwork.nodes[0]; i0++)
		{
			float temp0 = rdmClass.rdmGenerator();
			tempInput.push_back(temp0);
			if (visualIO)
			{
				cout << temp0 << ", ";
			}
		}
		if (debug)
		{
			newNetwork.DEBUG_Calculate(tempInput);
			vector<float> BP_Input;
			if (visualIO)
			{
				cout << "\n \n Outputs: \n";
				for (int node = 0; node < newNetwork.nodes[input_Layers - 1]; ++node)
				{
					float something = newNetwork.net[input_Layers - 1][node].value / (1 + abs(newNetwork.net[input_Layers - 1][node].value));
					BP_Input.push_back(newNetwork.net[input_Layers - 1][node].value / (1 + abs(newNetwork.net[input_Layers - 1][node].value)));
					cout << something << ", ";
				}
			}
			else
			{
				for (int node = 0; node < newNetwork.nodes[input_Layers - 1]; ++node)
				{
					BP_Input.push_back(newNetwork.net[input_Layers - 1][node].value / (1 + abs(newNetwork.net[input_Layers - 1][node].value)));
				}
			}
			newNetwork.DEBUG_backProp(BP_Input, true);
			cout << "\n\n" << newNetwork.net[1][0].xCordList.size();
			if (newNetwork.net[1][0].xCordList.size() >= 3)
			{
				for (const auto& layer : newNetwork.net)
				{
					for (phi::Node node : layer)
					{
						node.pointGrouper(3, true);
						node.BCConstructor(true);
					}
				}
			}
		}
		else
		{
			newNetwork.calculate(tempInput);
			vector<float> BP_Input;
			if (visualIO)
			{
				cout << "\n \n Outputs: \n";
				for (int node = 0; node < newNetwork.nodes[input_Layers - 1]; ++node)
				{
					float something = newNetwork.net[input_Layers - 1][node].value + 0;
					BP_Input.push_back(newNetwork.net[input_Layers - 1][node].value);
					cout << something << ", ";
				}
			}
			else
			{
				for (int node = 0; node < newNetwork.nodes[input_Layers - 1]; ++node)
				{
					BP_Input.push_back(newNetwork.net[input_Layers - 1][node].value);
				}
			}
			newNetwork.backProp(BP_Input);
			if (newNetwork.net[1][0].xCordList.size() >= 3)
			{
				for (const auto& layer : newNetwork.net)
				{
					for (phi::Node node : layer)
					{
						node.pointGrouper(3, true);
						node.BCConstructor(true);
					}
				}
			}
		}
		if (visualIO == false)
		{
			cout << "\n iteration #" << i + 1;
		}
	}

	cout << "\nFinished in " << time(nullptr) - timeStart << " seconds. \n";
	/*
		for (int node = 0; node < newNetwork.nodes[input_Layers - 1]; ++node)
		{
			float output = newNetwork.net[input_Layers - 1][node].value;
			cout << output << "\n";
		}*/
	cout << "done \n";
}

int main()
{
	bool thing = true;
	while (thing)
	{
		float something = 1 / 4;
		cout << "Would you like to make and run Phi Net? (y/n/b/b5) \n";
		string input;
		cin >> input;
		if (input == "n")
		{
			thing = false;
		}
		else if (input == "b")
		{
			DEBUG_calculateNetwork(true);
		}
		else if (input == "b5")
		{
			DEBUG_calculateNetwork(true, 5);
		}
		else
		{
			DEBUG_calculateNetwork(false);
		}
	}
} 