#pragma once
#include <vector>
#include <algorithm> 
#include <iostream>

using namespace std;

class BellNet
{
	signed short int CRS = 1;
	vector<signed short int> CRSVals = { 5 };
	vector<vector<vector<vector<int>>>> cords;		
	//cords[Layer][Node][coordinate pair index || { meta data and H,K pairs }][0=x, 1=y]

	//cords[~][~][0][0] = equation type ID ({BC,AX^B})  | -[0][1] = DataPointAmt  | -[0][2,3] = lower end gradient (10000/([2]x^[3])  | -[0][4,5] = upper end gradient (10000/([4]x^[5])
	//  | -[0][6+] odd = h  | -[0][6+] even = k

	//cords[~][~][CRS+ coordinate pair index][0] = x  | -[1] = y

	signed int iThreshold;

	BellNet(signed int Layers, vector<signed int>Nodes, signed int iterationThreshold, vector<int> DefaultLowerGradient, vector<int> DefaultUpperGradient)
	{
		iThreshold = iterationThreshold;

		for (int Layer = 0; Layer < Layers; Layer++)
		{
			cords.push_back({});
			for (int Node = 0; Node < Nodes[Layer]; Node++)
			{
				cords[Layer].push_back({});
				for (int i; i < CRS; i++)
				{
					cords[Layer][Node].push_back({});
					for (int i1; i1 < CRSVals[i1]; i1++)
					{
						cords[Layer][Node][i].push_back(0);
					}
				}
				cords.push_back({});
				cords[Layer][Node][0][2] = DefaultLowerGradient[0];
				cords[Layer][Node][0][3] = DefaultLowerGradient[1];
				cords[Layer][Node][0][4] = DefaultUpperGradient[0];
				cords[Layer][Node][0][5] = DefaultUpperGradient[1];
			}
		}
	}

	void updateBC()
	{
		for (int Layer; Layer < cords.size(); Layer++)
		{
			for (int Node; Node < cords.size(); Node++)
			{
				switch (cords[Layer][Node][0][0])
				{
				case 0: break;								// change this so that there aren't cases, just checking iteration 
				case 1: break;								// threshold for updateBC_1 ; make it so that BC_0_2 & BC_0_3 are
				case 2:										// automatic if included at all
					orderCoordinates(Layer, Node);
					updateBC_0_2(Layer, Node);
					break;
				case 3:
					updateBC_0_3(Layer, Node);
					break;
				default:
					updateBC_1(Layer, Node);
				}
			}
		}
	}

	void insertCoordinates(Layer, Node)
	{

	}

	void orderCoordinates(int Layer,int Node)
	{

	}
	void updateBC_0_2(int Layer, int Node)
	{
		cords[Layer][Node][0][7] = 2 * cords[Layer][Node][CRS + 1][1] / cords[Layer][Node][CRS + 1][0];
		cords[Layer][Node][0][6] = cords[Layer][Node][CRS + 1][0] / 2;
	}
	void updateBC_0_3(int Layer, int Node)
	{
		int x0 = cords[Layer][Node][CRS][0];
		int y0 = cords[Layer][Node][CRS][1];
		int x1 = cords[Layer][Node][CRS + 1][0];
		int y1 = cords[Layer][Node][CRS + 2][1];
		int x2 = cords[Layer][Node][CRS + 2][0];
		int y2 = cords[Layer][Node][CRS + 2][1];
		int x3 = cords[Layer][Node][CRS + 3][0];
		int y3 = cords[Layer][Node][CRS + 3][1];

		bool highLow = y1 > 2 * y2 * x1 / (2 * x2); // true = high

		if (y1 == 2 * y2 * x1 / (2 * x2))
		{
			cords[Layer][Node][0][7] = 2 * y2 / x2;
			cords[Layer][Node][0][6] = x2 / 2;
			return;
		}
		if (highLow == false)
		{
			cords[Layer][Node][0][6] = y2 * x1 ^ 2 / (y1 * x2);
		}
		else
		{
			cords[Layer][Node][0][6] = (x2 * y1 + x2 * x1 * (x1 / x2 - 2)) / (y1 - y2);
		}
	}
	void updateBC_1(int Layer, int Node)
	{
		//point and complexity calculations

		//H/K(s) eval:

	}

	int eval(int input, signed int Layer, signed int Node)
	{
		int k = cords[Layer][Node][0][6];

		if (input < cords[Layer][Node][CRS][0]) { return 10000 / (cords[Layer][Node][0][2] * input ^ cords[Layer][Node][0][3]); } // if x < lower bound, use that equation

		if (input > cords[Layer][Node][CRS][cords[Layer][Node][CRS].size() - 1]) { return 10000 / (cords[Layer][Node][0][4] * input ^ cords[Layer][Node][0][5]); } // if x > upper bound, use that equation

		if (input <= k) { return cords[Layer][Node][0][7] * input ^ 2 / (2 * k) + cords[Layer][Node][0][4]; }

		return cords[Layer][Node][0][7] * (input - k / 2 - (input - k) ^ 2 / (2 * (cords[Layer][Node][0][4] - k)));
	}
};