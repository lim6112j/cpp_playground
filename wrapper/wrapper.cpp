#include <iostream>
class Int {
  int data;
public:
  Int(int data) : data(data) {}
  Int(const Int& i) : data(i.data) {}
};
int main() {
}
