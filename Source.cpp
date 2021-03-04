
#pragma once
#include <vector>
#include <ctime>
#include <random>
#include <cstdlib>
#include "Node.h"

using namespace std;

namespace phi
{
	class Network
	{
	public:
		vector<vector<Node>> net;
		vector<unsigned int> nodes;
		unsigned int layers;
		unsigned int weightVariation = 10000; // max 10^x amount
		Network(unsigned int Layers, vector<unsigned int> Nodes)
		{
			layers = Layers;
			nodes = Nodes;
			Node stanNode;

			std::default_random_engine generator;													// for random weights
			std::uniform_int_distribution<int> distribution(0 - weightVariation, weightVariation);	//

			int maxConnections = 0;
			int maxNodes = 0;

			int errori = 0;

			//errori = 0;  cout << "check 1." << errori; errori++; // for checking for error location and etc

			net.push_back({});
			for (unsigned int node = 0; node < nodes[0]; node++)
			{
				net[0].push_back(stanNode);
			}
			for (int layer = 1; layer < layers; layer++) {
				net.push_back({});
				for (int node = 0; node < nodes[layer]; node++) {
					net[layer].push_back(stanNode);
					for (int connNum = 0; connNum < nodes[layer - 1]; connNum++)
					{
						int temp = distribution(generator);
						net[layer][node].connWeight.push_back(temp);	// allowing for variation in both pos and neg
						//cout << net[layer][node].connWeight[connNum] << "\n";
						//cout << net[layer][node].connWeight[connNum]; // note mem inefficiency
					}
				}
			}
		}

		void DEBUG_Calculate(vector<float> inputValues)
		{
			cout << "\n\nInitiating Calculation . . .";
			for (int layer = 0; layer < layers; layer++)
			{
				cout << "\n   Layer: " << layer;
				for (int node = 0; node < nodes[layer]; node++)
				{
					cout << "\n      Node: " << node;
					float input = 0;
					cout << "\n         inputs ";
					if (layer == 0)
					{
						cout << input;
						input = inputValues[node];
					}
					else
					{
						for (unsigned int connNum = 0; connNum < nodes[layer - 1]; connNum++)
						{
							input += net[layer - 1][connNum].value * net[layer][node].connWeight[connNum] / weightVariation;
						}
						cout << input;
					}
					net[layer][node].movingInp = input;
					float output = 0;
					unsigned int calcLength;

					if (input > net[layer][node].khList[net[layer][node].khList.size() - 2])			// possible bug: if size is index, or if right side != last k in sequence for other reason
					{																					//
						cout << "\n         Input is beyond khList... Proceeding with diminishing end protocol";	//
						for (int i = 2; i < net[layer][node].khList.size() - 2; i += 2)					// this is Calc for right side beyond plotted curve
						{
							output += (net[layer][node].khList[i] - net[layer][node].khList[i - 2]) * ((net[layer][node].khList[i + 1] - net[layer][node].khList[i - 1])
								/ 2 + net[layer][node].khList[i - 1]);
						}
						output = (input - net[layer][node].khList[net[layer][node].khList.size() - 2]) / (net[layer][node].dimSmoothing
							+ (input - net[layer][node].khList[net[layer][node].khList.size() - 2]));
					}
					else
					{
						for (calcLength = 0; input > net[layer][node].khList[calcLength]; calcLength += 2) {} // calcLength = the k after the input so if input=k+.00001		// Bell curve
						if (calcLength >= 2)																  // then calcLength = 2.											//
						{																																						//
							cout << "\n         Input is within khList... ";																												//
							for (int i = 2; i < calcLength; i += 2) // calculating all parts of bell curve that are fully defined (aka areas of whole right triangle)			// calculator
							{																																					// (This is
								output += (net[layer][node].khList[i] - net[layer][node].khList[i - 2]) * ((net[layer][node].khList[i + 1] - net[layer][node].khList[i - 1])	//  somewhat
									/ 2 + net[layer][node].khList[i - 1]);																										//  tested
							}																																					//  could still
							// (x-k0)( ((x-k0)*(h-h0))/(2(k-k0)) + h0 ) | Finding area of part of traingle																		//  have problems)
							output += (input - net[layer][node].khList[calcLength - 2]) * (((input - net[layer][node].khList[calcLength - 2]) *									//
								(net[layer][node].khList[calcLength + 1] - net[layer][node].khList[calcLength - 1])) / (2 * (net[layer][node].khList[calcLength]				//
									- net[layer][node].khList[calcLength - 2])) + net[layer][node].khList[calcLength - 1]);														//
							//cout << "output " << output;
							//cout << "\n";
							//cout << "\n";
						}
						else
						{
							cout << "\n         Input is beyond khList... Proceeding with diminishing end protocol";	//
							output += (net[layer][node].khList[1]) + (input / abs(input)) * sqrt(abs(input));	// bad lower end approx
						}
						//cout << output << "\n";
					}
					cout << "\n          Output: " << output;
					net[layer][node].value = output;
				}
			}
		}
	};
}