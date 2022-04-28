#include <stdio.h>
int main() {
  int a;
  int b;
  const int* pa = &a;
  *pa = 3; // error
  pa = &b;
  int* const ppa = &a;
  *ppa = 3;
  ppa = &b; // error
  return 0;
}
