#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

int main()
{
  string hello = "hello";


  for (int i = 0; i < hello.length(); i++)
  {
    if (islower(hello[i]))
    {
      hello[i] = toupper(hello[i]);
    }
  }

  cout << hello << endl;

  return 0;
}
