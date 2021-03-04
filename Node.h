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
		float movingInp;							// needed to make backprop more efficiently
		vector<float> khList;						// lines between (k,h) is the derivative of bell curve (should have and may change to list of ks and hs
		float endCords[2] = { 0, 0 };				// start cords and end cords

		vector<float> avDeviation;					// average deviation between last x and x (x, averageDeviation)
		vector<short int> connWeight;				// weight of connection (uncompressed via /10000)
		signed int connWeightAmt;					// general value of iterations that occurred

		float dimSmoothing;
		float dimHeight;
		int movingTrueVal;							// correct value that is used for back propagation
		int movingValWeighted;						// signed amount | value that the node contributed to the end result

		signed int compCordAmt;				
		vector<float> xCompCords;		
		vector<float> yCompCords;
		vector<float> xCordList;					
		vector<float> yCordList;

		// Value Throughput Functions (like sigmoid)
		void DirivMerge()
		{

		}
		int BCConstructor()
		{
			//constraint checker
			for (signed int i = 0; i < xCompCords.size(); i += 3)
			{
				// checking for upper constraint ( \frac{\left(x-x_{0}\right)\left(y_{2}-y_{0}\right)\left(2-\frac{x-x_{0}}{x_{2}-x_{0}}\right)}{x_{2}-x_{0}}+y_{0} )
				if ( ((xCompCords[i+1] - xCompCords[i]) * (yCompCords[i+2] -yCompCords[i]) * (2 - ((xCompCords[i+1] - xCompCords[i]) / (xCompCords[i+2] - xCompCords[i])))) 
					/ (xCompCords[i+2] - xCompCords[i]) + yCompCords[i] < xCompCords[i+1])
				{
					return 1;
				}
				// checking for lower constraint ( \frac{h\left(x-x_{0}\right)^{2}}{2\left(x_{2}-x_{0}\right)}+y_{0} )
				if ( ( (yCompCords[i+2]) - yCompCords[i]) * ( pow(xCompCords[i+1]- xCompCords[0], 2) ) / (pow(xCompCords[i+2] - xCompCords[i], 2)) + yCompCords[i] > xCompCords[i+1])
				{
					return 1;
				}
			}
			khList.clear();
			for (signed int i = 0; i < xCompCords.size(); i += 3)
			{
				// relative k0 & h0 (origin):
				khList.push_back(xCompCords[i]);
				khList.push_back(yCompCords[i]);
				// relative k1 & h1 (derivative vertex):
				if (0 > yCompCords[i+1]- yCompCords[i] - ( (yCompCords[i+2] - yCompCords[i]) * (xCompCords[i+1] - xCompCords[i]) ) / (xCompCords[i+2] - xCompCords[i]) )
				{
					khList.push_back(((xCompCords[i+2] - xCompCords[i]) * (yCompCords[i+1] - yCompCords[i]) + (yCompCords[i+2] - yCompCords[i]) * (xCompCords[i+1] - xCompCords[i]) *
						((xCompCords[i+1] - xCompCords[i]) / (xCompCords[i+2] - xCompCords[i]) - 2)) / (yCompCords[i+1] - yCompCords[i+2]));
				}
				else
				{
					khList.push_back((((yCompCords[i+2] - yCompCords[i]) * (xCompCords[i+1] - xCompCords[i]) * (xCompCords[i+1] - xCompCords[i])) / ((yCompCords[i+1] - yCompCords[i]) * // no ^ 2 because it doesn't
						(xCompCords[i+2] - xCompCords[i]))));																															 // accept float types
				}
				khList.push_back((2 * (yCompCords[i+2] - yCompCords[i])) / (xCompCords[i+2] - xCompCords[i]));
				// relative k2 & h2 (where derivitive == 0)
				khList.push_back(xCompCords[i+2]);
				khList.push_back(xCompCords[i+2]);
			}
		}
		void pointGrouper(signed int amountOfOutputPoints) // MAKE SURE IS DEVISABLE BY THREE, DON'T CALCULATE MORE POINTS THAN PREV IT
		{
			// Segmented into 3 via x cord amt and then averaged (I.E. | 1,1,2 | 5,6,9 | 10,15,100 | ). This is a bad way of going about this.
			// This needs to be changed into a function that is better
			// Doesn't conform to constraints of BCConstructor
			signed int outPoints = amountOfOutputPoints;
			float k = 0;
			float h = 0;
			signed int lastPos = 0;
			vector<float> xTempCordList;
			vector<float> yTempCordList;
			for (signed int slice = 0; slice < outPoints; outPoints++)
			{
				signed int index = lastPos;
				for (; index < xCordList.size() / outPoints; index++)
				{																	// first third is used as an iteration amount here
					k += xCordList[index];											//
					h += yCordList[index];											//
				}																	// and then by the end, it equals xCordList.size() / 3 rounded up
				if (xCompCords.size() == amountOfOutputPoints)
				{
					xTempCordList.push_back(( xCompCords[slice] * compCordAmt + k) / (compCordAmt + index));
					yTempCordList.push_back((yCompCords[slice] * compCordAmt + h) / (compCordAmt + index));
				}
				else
				{
					xTempCordList.push_back(k / index);
					xTempCordList.push_back(h / index);
				}
				lastPos = index;
			}
			xCompCords = { xTempCordList };
			yCompCords = { yTempCordList };
		}
		int addOrderedCords(vector<float> xcords, vector<float> ycords)	// not most efficient
		{
			if (xcords.size() != ycords.size())
			{
				return 1;
			}
			if (xCordList.empty())
			{
				//cout << "\nstarting empty protocol";
				//cout << "\nadding " << xcords[0] << ", " << ycords[0];
				xCordList.push_back(xcords[0]);
				yCordList.push_back(ycords[0]);
				xcords.erase(xcords.begin());
				ycords.erase(ycords.begin());
			}
			if (xcords.empty()) { return 0; }
			auto position = xCordList.begin();
			for (unsigned int index = 0; index < xcords.size()-1; index++)
			{
				if (xcords[index] < xCordList[xCordList.size() - 1])
				{
					while (*position < xcords[index])
					{
						++position;
					}
					xCordList.insert(position, xcords[index]);
					yCordList.insert(position, ycords[index]);
				}
				else
				{
					xCordList.push_back(xcords[index]);
					yCordList.push_back(ycords[index]);
				}
			}
			return 0;
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
