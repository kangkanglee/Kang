#include <iostream>  

using namespace std;
int total = 0;

void fullPermutation(int* fullArray, int start, int end) { 
  if (start >= end) {
    for (int i = 0; i <= end; i++) {
      cout << fullArray[i];
    }
    cout << endl;
    total++;
  }
  else {
    for (int i = start; i <= end; i++) {
      swap(fullArray[start], fullArray[i]); //swap
      fullPermutation(fullArray, start + 1, end);
      swap(fullArray[start], fullArray[i]); //recover  
    }
  }
}
int main()
{
  int number; // total of numbers
  cout << "Number:" << endl;
  cin >> number;
  int* fullArray = new int[number]; //allocate memory  
  // initialize
  for (int i = 0; i < number; i++)
  {
    fullArray[i] = i + 1;
  }
  fullPermutation(fullArray, 0, number - 1);
  cout << "Total = " << total << endl;
  return 0;
}
