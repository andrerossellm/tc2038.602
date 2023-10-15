#include <iostream>
#include "sais.cpp"
using namespace std;

int main() {
  string toRead = "CICOCA$";
  vector<int> T;
  for (auto & c : toRead) 
    T.push_back((int) c);
  vector<int> SA(T.size(), -1);

  sais(T, SA);

  cout << "[ ";
  for (auto & el : SA)
    cout << el << " ";
  cout << "]"<< endl;
  return 0;
}