#include <iostream>
using namespace std;
// global var
int num;
// func declaration
int &test();
int &test() {
  return num;
}
int main() {
  test() = 5;
  cout << num << endl;
  return 0;
}
