#include <vector>

using namespace std;

class Net
{
public:
	Net(const vector<unsigned> &topology);
	void feedForward(inputs);
	void backProp(targetVals);
	void getResults(resultVals) const;

private:

};

int main()
{
	Net myNet(topology);

	vector<double> inputVals;
	myNet.feedForwayd(inputVals);

	vector<double> targetVals;
	myNet.backProp(targetVals);

	vector<double> resultVals;
	myNet.getResults(resultVals;
}