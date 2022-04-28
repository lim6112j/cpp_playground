#include <iostream>
#include <memory>
using namespace std;
class Person {
  private:
  string name_;
  int age_;
public:
  Person(const string& name, int age);
  ~Person() { cout << "소멸자가 호출됨" << endl; }
  void ShowPersonInfo();
};
int main() {
  //unique_ptr<Person> hong = make_unique<Person>("길동", 29);
  //hong->ShowPersonInfo();
  //cout << "shared ptr" << endl;
  shared_ptr<Person> hong2 = make_shared<Person>("동길", 20);
  cout << "현재 소유자수 : " << hong2.use_count() << endl;
  auto han = hong2;
  cout << "현재 소유자수 : " << hong2.use_count() << endl;
  //han.reset();
  //cout << "현재 소유자수 : " << hong2.use_count() << endl;
  return 0;
}
Person::Person(const string &name, int age) {
  name_ = name;
  age_ = age;
  cout << "생성자가 호출되었습니다." << endl;
}
void Person::ShowPersonInfo() { cout << name_ << "의 나이는 " << age_ << "살입니다." << endl; }
