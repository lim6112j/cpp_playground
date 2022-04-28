#include <iostream>
#include <cstring>
class MyString {
  char *string_content;
  int string_length;
  int memory_capacity;
public:
  MyString();
  // construct from string
  MyString(const char* str);
  // copy constructor
  MyString(const MyString &str);
  // move constructor
  MyString(MyString &&str) noexcept;
  void reserve(int size);
  MyString operator+(const MyString &s);
  MyString &operator=(const MyString &s);
  ~MyString();
  int length() const;
  void print();
  void println();
};
MyString::MyString() {
  std::cout << "생성자 호출" << std::endl;
  string_length = 0;
  memory_capacity = 0;
  string_content = nullptr;
}
MyString::MyString(const char *str) {
  std::cout << "생성자 호출" << std::endl;
  string_length = strlen(str);
  memory_capacity = string_length;
  string_content = new char[string_length];
  for (int i = 0; i != string_length; i++) {
    string_content[i] = str[i];
  }
}
MyString::MyString(const MyString &str) {
  std::cout << "복사 생성자 호출" << std::endl;
  string_length = str.string_length;
  memory_capacity = str.string_length;
  string_content = new char[string_length];
  for (int i = 0; i != string_length; i++){
    string_content[i] = str.string_content[i];
  }
}
MyString::MyString(MyString &&str) noexcept {
  std::cout << "이동 생성자 호출" << std::endl;
  string_length = str.string_length;
  string_content = str.string_content;
  memory_capacity = str.memory_capacity;
  str.string_content = nullptr;
}
MyString::~MyString() {
  delete[] string_content;
}
MyString &MyString::operator=(const MyString &s) {
  std::cout << "복사!" << std::endl;
  if(s.string_length > memory_capacity) {
    delete[] string_content;
    string_content = new char[s.string_length];
    memory_capacity = s.string_length;
  }
  string_length = s.string_length;
  for (int i = 0; i != string_length; i++) {
    string_content[i] = s.string_content[i];
  }
  return *this;
}
void MyString::reserve(int size) {
  if(size > memory_capacity) {
    char *prev_string_content = string_content;
    string_content = new char[size];
    memory_capacity = size;
    for (int i = 0; i != string_length; i++) {
      string_content[i] = prev_string_content[i];
    }
    if(prev_string_content != nullptr) delete[] prev_string_content;
  }
}
MyString MyString::operator+(const MyString &s) {
  MyString str;
  str.reserve(string_length + s.string_length);
  for (int i = 0; i < string_length; i++) {
    str.string_content[i] = string_content[i];
  }
  for (int i = 0; i < s.string_length; i++) {
    str.string_content[string_length + i] = s.string_content[i];
  }
  str.string_length = string_length + s.string_length;
  return str;
}
int MyString::length() const {return string_length;}
void MyString::print() {
  for (int i = 0; i != string_length; i++) {
    std::cout << string_content[i];
  }
}
void MyString::println() {
  for (int i = 0; i != string_length; i++) {
    std::cout << string_content[i];
  }
  std::cout << std::endl;
}
template <typename T>
void my_swap(T &a, T &b) {
  T tmp(a); // T tmp = a;
  a = b;
  b = tmp;
}
int main() {
  MyString str1("abc");
  MyString str2("def");
  std::cout << "swap 전 --------------------" << std::endl;
  str1.println();
  str2.println();
  std::cout << "swap 후 --------------------" << std::endl;
  my_swap(str1, str2);
  str1.println();
  str2.println();
  MyString str3 = str1 + str2;
  std::cout << str3.length() << std::endl;
  str3.println();
}
