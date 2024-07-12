/*
1.10.5: Comparing and copying vectors.

If the vector oldData is the same as the vector newData, print "Data matches!" ended with a newline. Otherwise, assign oldData with newData.
Ex: If oldData = {10, 12, 18, 16} and newData = {25, 27, 29, 23}, then oldData becomes {25, 27, 29, 23}.
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	const int NUM_POINTS = 4;
	vector<int> oldData(NUM_POINTS);
	vector<int> newData(NUM_POINTS);
	unsigned int i;

	for (i = 0; i < oldData.size(); ++i)
	{
		cin >> oldData.at(i);
	}

	for (i = 0; i < newData.size(); ++i)
	{
		cin >> newData.at(i);
	}

	/* Your solution goes here  */
	bool dataMatches = true;
	for (i = 0; i < oldData.size(); i++)
	{
		int oldValue = oldData.at(i);
		int newValue = newData.at(i);

		if (oldValue != newValue)
		{
			dataMatches = false;
			oldData.at(i) = newValue;
		}
	}

	if (dataMatches)
	{
		cout << "Data matches!" << endl;
	}

	for (i = 0; i < oldData.size(); ++i)
	{
		cout << oldData.at(i) << " ";
	}
	cout << endl;

	return 0;
}