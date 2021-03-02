#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

namespace phi
{
	class Node // ~ 900 nodes (with prev node at 900) = 1mb
	{
	public:

		float value;
		float movingInp;							// needed to make backprop more effiecent
		vector<float> khList;						// lines between (k,h) is the derivative of bell curve (should have and may change to list of ks and hs
		float endCords[4] = { 0, 0 };				// start cords and end cords
		vector<float> avDeviation;					// average deviation between last x and x (x, averageDeviation)
		vector<float> cordList;						// derived from back propagation
		vector<short int> connWeight;				// weight of connection (uncompressed via /10000)
		signed int connWeightAmt;					// general value of iterations that occurred
		float dimSmoothing;
		float dimHeight;
		int movingTrueVal;							// correct value that is used for back propagation
		int movingValWeighted;						// signed amount | value that the node contributed to the end result
		vector<float> xCordList;					
		vector<float> yCordList;

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

		void addKHCords(vector<float> cords)
		{
			// note some weirdness with 2 ++positions/1 --position and differences between -1 and -2 and etc are to make sure that upon adding values the position is at the h before the k after value
			auto position = khList.begin();

			for (int i = 0; i < cords.size() - 2; i += 2)		// through extensive bug fixing, there is no longer any bugs
			{
				if (khFirstPass)
				{
					//cout << "_3b \n";
					khList.push_back(cords[i]);
					khList.push_back(cords[i + 1]);
					khFirstPass = true;
				}
				else
				{
					position = khList.begin();
					if (khList.size() > 10)	//1a																				// this is for potential optimization of process ( check efficiency of ++position to validate/invalidate )
					{
						//cout << "1a \n";
						if (cords[i] < khList[khList.size() - 2] && cords[i] > khList[0])
						{
							float guess = cords[i] / khList[khList.size() - 2];
							for (int i = 0; i < round(guess / 2) * 2; i++) { ++position; }	 									// division & multiplication of 2 is to make sure that it is even so that it corresponds to k
							if (cords[i] > *position) { while (cords[i] > *position) { ++position; ++position; } }				// --position because insert pushes indexed value back ( so it is like putting value
							else { while (cords[i] < *position) { --position; --position; } ++position; ++position; }			// between position and position++) ( and thus position should be list k before input k )
							--position;
						}
						else if (cords[i] > khList[khList.size() - 2])									// For in case that
						{																				// the inputed K values
							for (int i = 0; i < khList.size() - 1; i++)									// are either greater
							{																			// or smaller than
								++position;																// the respective greatest
							}																			// or smallest ks already in list
						}
					}
					else //1b
					{
						//cout << "1b \n";
						if (cords[i] < khList[khList.size() - 2] && cords[i] > khList[0])
						{
							for (int i = 0; cords[i] > *position && i < khList.size() - 1; i += 2) //2.1a
							{
								//cout << "2.1a \n";
								++position;
								++position;
							}
							--position;
						}
						else if (cords[i] > khList[khList.size() - 2])
						{
							for (int i = 0; i < khList.size() - 1; i++)
							{
								++position;
							}
						}
					}
					//cout << "_3a \n";
					if (cords[i] == *position)//3.1a				// in case that they share the same x value,
					{												// average current y and new y. Note: if x values correspond too often,
						//cout << "_3.1a \n";
						auto hPos = ++position;						// there will be a disproportionate amount of weight on new y over
						*position = (*hPos + cords[i + 1]) / 2;		// previous ys
					}
				}
			}
		}
	private:
		bool khFirstPass = true;
		bool indexTwoGap = true;
		bool indexOneGap = true;
	};
}
