#pragma once
class BellNet
{
	vector<vector<vector<vector<int>>>> cords; 
	signed int CRS = 1; 
	//cords[~][~][0][0] = DataPointAmt  | -[0][1,2] = x0, y0  | -[0][3,4] = xEnd, yEnd  | -[0][5+] odd = h  | -[0][5+] even = k

	signed int iThreshold;

	BellNet(signed int Layers, vector<signed int>Nodes, signed int iterationThreshold)
	{
		iThreshold = iterationThreshold;

		cords.push_back({});
		for (int Layer = 0; Layer < Layers; Layer++)
		{
			cords.push_back({});
			for (int Node = 0; Node < Nodes[Layer]; Node++)
			{
				cords.push_back({});
			}
		}
	}

	void updateBC()
	{
		for (int Layer; Layer < cords.size(); Layer++)
		{
			for (int Node; Node < cords.size(); Node++)
			{
				if (cords[Layer][Node][0][0] == 3)
				{
					updateBC_0(Layer,Node);
				}
			}
		}
	}

	void updateBC_0(int Layer, int Node)
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
			cords[Layer][Node][0][5] = 2 * y2 / x2;
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

	int eval(int input, signed int Layer, signed int Node)
	{
		int k = cords[Layer][Node][0][6];
		if (input<= k) { return cords[Layer][Node][0][5] * input^ 2 / (2 * k) + cords[Layer][Node][0][3]; }
		// else not needed
		return cords[Layer][Node][0][5] * (input- k / 2 - (input- k) ^ 2 / (2 * (cords[Layer][Node][0][3] - k)));
	}
};

