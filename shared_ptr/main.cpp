#include <iostream>
#include <vector>
using namespace std;
class A {
  int *data;

public:
  A() {
    data = new int[100];
    std::cout << "자원을 획득" << std::endl;
  }
  ~A() {
    std::cout << "소멸자 호출!" << std::endl;
    delete[] data;
  }
};

class Node {
  std::vector<std::shared_ptr<Node>> children;
  std::weak_ptr<Node> parent;

public:
  Node();
  void addChild(std::shared_ptr<Node> node) { children.push_back(node); }
};

int main(int argc, char *argv[]) {
  std::vector<std::shared_ptr<A>> vec;
  vec.push_back(std::shared_ptr<A>(new A()));
  vec.push_back(std::shared_ptr<A>(vec[0]));
  vec.push_back(std::shared_ptr<A>(vec[1]));

  // 천번째 원소 소멸
  std::cout << "첫번째 소멸!" << std::endl;
  vec.erase(vec.begin());

  // 그다음 원소 소멸
  std::cout << "다음 원소 소멸" << std::endl;
  vec.erase(vec.begin());

  // 마지막 원소 소멸
  std::cout << "마지막 원소 소멸" << std::endl;
  vec.erase(vec.begin());

  std::cout << "프로그램 종료" << std::endl;

  A *a = new A();
  std::shared_ptr<A> pa1(a);
  std::shared_ptr<A> pa2(a);

  std::cout << pa1.use_count() << std::endl;
  std::cout << pa2.use_count() << std::endl;

  return 0;
}
