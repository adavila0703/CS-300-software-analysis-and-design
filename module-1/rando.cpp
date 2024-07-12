#include <iostream>
#include <vector>
using namespace std;

int main()
{
  const int NUM_ELEMENTS = 8;
  vector<int> revVctr = {1, 2, 3, 4};
  unsigned int i;
  int tmpValue;

  // Reverse
  for (i = 0; i < (revVctr.size() / 2); ++i)
  {
    tmpValue = revVctr.at(i); // These 3 statements swap
    revVctr.at(i) = revVctr.at(revVctr.size() - 1 - i);
    revVctr.at(revVctr.size() - 1 - i) = tmpValue;
  }

  // Print values
  cout << endl
       << "New values: ";
  for (i = 0; i < revVctr.size(); ++i)
  {
    cout << " " << revVctr.at(i);
  }
  cout << endl;

  return 0;
}