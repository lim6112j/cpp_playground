#include <iostream>
class A {
  mutable int data_;
public:
  A(int data) : data_(data) {};
  void doSomething(int x) const {
    data_ = x;
  }
  void printData() const {
    std::cout << "data: " << data_ << std::endl;
  }
};
int main() {
  A a(10);
  a.doSomething(3);
  a.printData();
}
