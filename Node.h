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

		void addKHCords(vector<float> cords)
		{
			auto position = khList.begin();

			for (int i = 0; i < cords.size() - 2; i += 2)		// through extensive bug fixing, there is no longer any bugs
			{
				position = khList.begin();
				if (khList.size() > 10)	//1a															// this is for potential optimization of process ( check efficiency of ++position to validate/invalidate )
				{
					//cout << "1a \n";
					float guess = cords[i] / khList[khList.size() - 2];
					for (int i = 0; i < round(guess * khList.size() / 2) * 2; ++i) { ++position; }		// division & multiplication of 2 is to make sure that it is even so that it corresponds to k
					if (cords[i] > *position) { for (position; cords[i] > *position; ++position) {} }	// --position because insert pushes indexed value back ( so it is like putting value
					else { for (position; cords[i] < *position; --position) {} ++position; }			// between position and position++) ( and thus position should be list k before input k )
					--position;
				}
				else //1b
				{
					//cout << "1b \n";
					const signed int khListSize = khList.size();
					for (int iSub = 0; iSub < khListSize; ++iSub) //2a 
					{ 
						//cout << "2a \n";
						if (cords[i] > *position) //2.1a
						{ 
							//cout << "2.1a \n";
							++position;
						}
						else //2.1b
						{
							//cout << "2.1b \n"; 
							--position;
							iSub = khListSize;
						}
					}
				}


				if (khListPass)//3a
				{
					//cout << "3 \n";
					if (cords[i] == *position)//3.1a				// in case that they share the same x value,
					{												// average current y and new y. Note: if x values correspond too often,
						//cout << "3.1a \n";
						auto hPos = ++position;						// there will be a disproportionate amount of weight on new y over
						*position = (*hPos + cords[i + 1]) / 2;		// previous ys
					}
					else//3.1b
					{
						//cout << "3.1b \n";
						khList.insert(position, cords[i]);
						khList.insert(position, cords[i + 1]);
					}
				}
				else//3b
				{
					//cout << "3b \n";
					khList.push_back(cords[i]);
					khList.push_back(cords[i + 1]);
				}
			}
		}
	private:
		bool khListPass = false;
		bool indexTwoGap = true;
		bool indexOneGap = true;
	};
}
