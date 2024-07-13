/*
1.14.1: Find 2D array max and min.

Find the maximum value and minimum value in milesTracker.
Assign the maximum value to maxMiles, and the minimum value to minMiles.

Sample output for the given program:

Min miles: -10
Max miles: 40
*/

#include <iostream>
using namespace std;

int main()
{
	const int NUM_ROWS = 2;
	const int NUM_COLS = 2;
	int milesTracker[NUM_ROWS][NUM_COLS];
	int i;
	int j;
	int maxMiles = 0; // Assign with first element in milesTracker before loop
	int minMiles = 0; // Assign with first element in milesTracker before loop
	int value;

	for (i = 0; i < NUM_ROWS; i++)
	{
		for (j = 0; j < NUM_COLS; j++)
		{
			cin >> value;
			milesTracker[i][j] = value;
		}
	}

	/* Your solution goes here  */

	minMiles = milesTracker[0][0];
	maxMiles = milesTracker[0][0];

	for (i = 0; i < NUM_ROWS; i++)
	{
		for (j = 0; j < NUM_COLS; j++)
		{
			int mileNumber = milesTracker[i][j];

			if (mileNumber > maxMiles)
			{
				maxMiles = mileNumber;
			}

			if (mileNumber < minMiles)
			{
				minMiles = mileNumber;
			}
		}
	}

	cout << "Min miles: " << minMiles << endl;
	cout << "Max miles: " << maxMiles << endl;

	return 0;
}