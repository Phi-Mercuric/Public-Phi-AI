#pragma once
#include <vector>
#include "Node.h"

using namespace std;

namespace phi
{
	class Network
	{
	public:
		vector<vector<Node>> net;
		vector<signed int> nodes;
		signed int layers;

		Network(signed int Layers, vector<signed int> Nodes)
		{
			layers = Layers;
			nodes = Nodes;
			Node stanNode;
			signed int weightVariation = 10000;
			net.push_back({});
			for (signed int node = 0; node < nodes[0]; node++)
			{
				net[0].push_back(stanNode);
			}
			for (int layer = 1; layer < layers; layer++) {
				net.push_back({});
				for (int node = 0; node < nodes[layer]; node++) {
					net[layer].push_back(stanNode);
					for (int connNum = 0; connNum < nodes[layer - 1]; connNum++)
					{
						signed int temp1 = rand() % (2 * weightVariation) - weightVariation;
						float temp2 = temp1 / weightVariation;
						net[layer][node].connWeight.push_back(temp2); // allowing for variation in both pos and neg
					}																									 // note mem inefficiency 
				}
			}
		}

		void backProp(vector<signed int> trueOutputNodes)
		{
		}
		void calculate(vector<float> inputValues)
		{
			for (int node = 0; node < nodes[0]; node++)		//Filling in input layer
			{												//
				net[0][node].value = inputValues[node];		//
			}												//
			for (int layer = 1; layer < layers; layer++)
			{
				for (int node = 0; node < nodes[layer]; node++)
				{
					float input = 0;																	// calculating total
					for (signed int connNum = 0; connNum < nodes[layer - 1]; connNum++)					// weight * value
					{																					// calculations
						input += net[layer - 1][connNum].value * net[layer][node].connWeight[connNum];  //
						cout << net[layer - 1][connNum].value << "\n";
						cout << net[layer][node].connWeight[connNum] << "\n\n\n\n\n";
					}																					//
					cout << input << "\n";
					float output = 0;
					signed short int calcLength;

					for (calcLength = 0; input > net[layer][node].khList[calcLength]; calcLength += 2) {  } // calcLength = the k after the input						// Bell curve
					for (int i = 2; i < calcLength; i += 2) // calculating all parts of bell curve that are fully defined (aka areas of whole right triangle)			// calculator
					{																																					// (This is
						output += (net[layer][node].khList[i] - net[layer][node].khList[i - 2]) * ((net[layer][node].khList[i + 1] - net[layer][node].khList[i - 1])	//  somewhat
							/ 2 + net[layer][node].khList[i - 1]);																										//  tested
					}																																					//  could still
					// (x-k0)( ((x-k0)*(h-h0))/(2(k-k0)) + h0 ) | Finding area of part of traingle																		//  have problems)
					output += (input - net[layer][node].khList[calcLength - 2]) * (((input - net[layer][node].khList[calcLength - 2]) *									//
						(net[layer][node].khList[calcLength + 1] - net[layer][node].khList[calcLength - 1])) / (2 * (net[layer][node].khList[calcLength]				//
							- net[layer][node].khList[calcLength - 2])) + net[layer][node].khList[calcLength - 1]);														//
					cout << output;
					cout << "\n";
					cout << "\n";
					net[layer][node].value = output;

				}
			}
		}
	};
}
