/*
1.10.3: Modify vector elements using other elements.
Write a loop that sets each vector element to the sum of itself and the next element,
except for the last element which stays the same. Be careful not to index beyond the last element. Ex:

Initial scores:        10, 20, 30, 40
Scores after the loop: 30, 50, 70, 40
The first element is 30 or 10 + 20, the second element is 50 or 20 + 30, and the third element is 70 or 30 + 40. The last element remains the same.
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	const int SCORES_SIZE = 4;
	vector<int> bonusScores(SCORES_SIZE);
	unsigned int i;

	for (i = 0; i < bonusScores.size(); ++i)
	{
		cin >> bonusScores.at(i);
	}

	/* Your solution goes here  */
	int lastIndex = bonusScores.size() - 1;

	for (i = 0; i < bonusScores.size(); i++)
	{
		if (i == lastIndex)
		{
			break;
		}

		bonusScores.at(i) += bonusScores.at(i + 1);
	}

	for (i = 0; i < bonusScores.size(); ++i)
	{
		cout << bonusScores.at(i) << " ";
	}
	cout << endl;

	return 0;
}