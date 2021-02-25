#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

namespace phi
{
	class Node
	{
	public:

		float value;
		vector<float> khList;				// lines between (k,h) is the derivative of bell curve
		float sted[4] = { 0, 0, 0, 0 };		// start cords and end cords
		vector<float> avDeviation;			// average deviation between last x and x (x, averageDeviation)
		vector<float> cordList;				// derived from back propagation
		vector<float> connWeight;			// weight of connection				
		float dimSmoothing;
		float dimHeight;

		// Value Throughput Functions (like sigmoid)
		void DirivMerge()
		{
		}
		void BCConstructor()
		{
		}
		void pointGrouper()
		{
		}
		void orderCoordinates()
		{
		}

		// FIX FOLLOWING:
		void addKHCords(vector<float> cords)
		{
			for (int i = 1; i < cords.size(); i += 2)
			{
				if (indexTwoGap)
				{
					if (indexOneGap)
					{
						sted[0] = cords[i - 1];
						sted[1] = cords[i];
						indexOneGap = false;
					}
					else
					{
						sted[2] = cords[i - 1];
						sted[3] = cords[i];
						indexTwoGap = false;
					}
				}
				else
				{
					khList.push_back(cords[i - 1]);
					khList.push_back(cords[i]);
				}
			}
		}
	private:
		bool indexTwoGap = true;
		bool indexOneGap = true;
	};
}
