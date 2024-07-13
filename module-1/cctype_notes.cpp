
#include <iostream>
#include <cctype>
using namespace std;

int main()
{
  const int MAX_LEN = 30; // Max string length
  char userStr[MAX_LEN];  // User defined string
  int i;

  // Prompt user to enter string
  cout << "Enter string (<"
       << MAX_LEN << " chars): ";
  cin >> userStr;

  cout << "Original: " << userStr << endl;

  cout << "isalpha:  ";
  for (i = 0; userStr[i] != '\0'; ++i)
  {
    if (isalpha(userStr[i]))
    {
      cout << "Y";
    }
    else
    {
      cout << "N";
    }
  }
  cout << endl;

  cout << "isdigit:  ";
  for (i = 0; userStr[i] != '\0'; ++i)
  {
    if (isdigit(userStr[i]))
    {
      cout << "Y";
    }
    else
    {
      cout << "N";
    }
  }
  cout << endl;

  cout << "isupper:  ";
  for (i = 0; userStr[i] != '\0'; ++i)
  {
    if (isupper(userStr[i]))
    {
      cout << "Y";
    }
    else
    {
      cout << "N";
    }
  }
  cout << endl;

  for (i = 0; userStr[i] != '\0'; ++i)
  {
    userStr[i] = toupper(userStr[i]);
  }
  cout << "After toupper: " << userStr << endl;

  return 0;
}