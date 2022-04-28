#include <stdio.h>
int main() {
  int arr[3] = {1,2,3};
  int (*parr)[3] = &arr; // pointer of 3 elements array
  printf("arr[1] : %d \n", arr[1]);
  printf("parr[1] : %d \n", (*parr)[1]); // value of parr(*parr) is the address of arr
}
