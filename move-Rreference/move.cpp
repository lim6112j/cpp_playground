#include <iostream>
class A {
public:
  A() { std::cout << "일반 생성자 호출!" << std::endl;}
  A(const A& a) { std::cout << "복사 생성자 호출!" << std::endl;}
  A(A&& a) { std::cout << "이동 생성자 호출!" << std::endl;}
  void aPrint(){std::cout << "test print\n";}
};
class B {
public:
  B(A&& a) : a_(std::move(a)) {};
  A a_;
};
int main() {
  A a;
  std::cout << "--------------" << std::endl;
  A b(a);
  std::cout << "--------------" << std::endl;
  A c(std::move(a));
  std::cout << "create B-- \n";
  B d(std::move(a));
  a.aPrint();
}
