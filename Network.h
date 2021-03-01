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
		vector<signed int> nodes;
		signed int layers;
		signed int weightVariation = 10000; // max 10^x amount
		Network(signed int Layers, vector<signed int> Nodes)
		{
			layers = Layers;
			nodes = Nodes;
			Node stanNode;

			std::default_random_engine generator;													// for random weights
			std::uniform_int_distribution<int> distribution(0-weightVariation, weightVariation);	//

			int maxConnections = 0;
			int maxNodes = 0;

			int errori = 0;

			//errori = 0;  cout << "check 1." << errori; errori++; // for checking for error location and etc

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
						int temp = distribution(generator);
						net[layer][node].connWeight.push_back(temp);	// allowing for variation in both pos and neg
						//cout << net[layer][node].connWeight[connNum] << "\n";
						//cout << net[layer][node].connWeight[connNum]; // note mem inefficiency
					}											     
				}
			}
		}

		void backProp(vector<float> outputValues)
		{
			for (int layer = layers - 1; layer > 0; layer--)
			{

				if (layer == layers-1)
				{
					for (int node = 0; node < nodes[layer]; node++)
					{
						net[layer][node].cordList.push_back( net[layer][node].movingInp );
						net[layer][node].cordList.push_back( outputValues[node] );
						net[layer][node].movingTV = outputValues[node];
						for (int conn = 0; conn < nodes[layer-1]; conn++)
						{
							net[layer][node].connWeight[conn] = (net[layer][node].connWeight[conn] + net[layer - 1][node].value) / net[layer][node].connWeightAmt[conn];
						}
					}
				}
				else
				{
					for (int node = 0; node < nodes[layer]; node++)
					{
						float output = 0;
						net[layer][node].cordList.push_back( net[layer][node].movingInp );
						for (int upNode = 0; upNode < nodes[layer + 1]; upNode++)
						{
							output += net[layer][upNode].movingTV * net[layer][upNode].connWeight[node];
						}
						net[layer][node].cordList.push_back(output / nodes[layers]);

						for (int conn = 0; conn < nodes[layer - 1]; conn++)
						{
							net[layer][node].connWeight[conn] = (net[layer][node].connWeight[conn] + net[layer - 1][node].value) / net[layer][node].connWeightAmt[conn];
						}
					}
				}
			}
		}
		void calculate(vector<float> inputValues)
		{
			for (int layer = 0; layer < layers; layer++)
			{
				for (int node = 0; node < nodes[layer]; node++)
				{
					float input = 0;
					// input calcs:
					if (layer == 0)
					{
						input = inputValues[node];		
					}
					else 
					{
						for (signed int connNum = 0; connNum < nodes[layer - 1]; connNum++)										
						{																									
							input += net[layer - 1][connNum].value * net[layer][node].connWeight[connNum] / weightVariation;
						}
					}
					net[layer][node].movingInp = input;
					float output = 0;
					signed short int calcLength;

					if (input > net[layer][node].khList[net[layer][node].khList.size() - 2])			// possible bug: if size is index, or if right side != last k in sequence for other reason
					{																					// 
						for (int i = 2; i < net[layer][node].khList.size() - 2; i += 2)					// this is Calc for right side beyond plotted curve
						{
							output += (net[layer][node].khList[i] - net[layer][node].khList[i - 2]) * ((net[layer][node].khList[i + 1] - net[layer][node].khList[i - 1])
								/ 2 + net[layer][node].khList[i - 1]);
						}
						input - net[layer][node].khList[net[layer][node].khList.size() - 2];
					}
					else
					{
						for (calcLength = 0; input > net[layer][node].khList[calcLength]; calcLength += 2) {} // calcLength = the k after the input								// Bell curve
						if (calcLength >= 2)																																	//
						{																																						//
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
							output += (net[layer][node].khList[1]) + (input / abs(input)) * sqrt(abs(input));	// bad lower end approx
						}
						net[layer][node].value = output;
						}
				}
			}
		}
	};
}
