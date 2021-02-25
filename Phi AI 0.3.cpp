#include <iostream>
#include <vector>
#include "Node.h"
#include "Network.h"

int main()
{
	phi::Network newNetwork(5, { 1,10,50,5,1 });
	for (signed short int layer = 0; layer < newNetwork.layers; layer++)
	{
		for (signed int node = 0; node < newNetwork.nodes[layer]; node++)
		{
			newNetwork.net[layer][node].addKHCords({ 0,0,0,0 });
			newNetwork.net[layer][node].addKHCords({ -1220, 10, 0, 5, 5, 10, 10, 20, 50, 100, 1220, 1, 99999, 99999 });
		}
	}
	newNetwork.calculate({ 100 });
	for (int layer = 0; layer < newNetwork.layers; layer++)
	{
		for (int node = 0; node < newNetwork.nodes[layer]; node++)
		{
			cout << newNetwork.net[layer][node].value << "\n";
		}
		cout << "\n";
	}
}