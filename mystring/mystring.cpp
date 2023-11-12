#include <cstring>
#include <iostream>
class MyString {
  char *str;
  int str_len;
  int memory_cap;

public:
  explicit MyString(int capacity);
  explicit MyString(char c);
  MyString(const char *str);
  MyString(const MyString &str);
  ~MyString();
  int length() const;
  void print() const;
  void println() const;
  MyString &assign(const char *s);
  MyString &assign(const MyString &str);
  int capacity() const;
  void reserve(int size);
  char at(int i) const;
  MyString &insert(int loc, const MyString &o);
  MyString &insert(int loc, const char *s);
  MyString &insert(int loc, char c);
  MyString &erase(int loc, int num);
  int find(int find_from, MyString &o) const;
  int find(int find_from, const char *s) const;
  int find(int find_from, char c) const;
  int compare(const MyString &o) const;
  // 연산자 오버로딩
  bool operator==(MyString &o);
  // [] operator overloading
  char &operator[](const int index);
};
MyString::MyString(int capacity) {
  str = new char[capacity];
  str_len = 0;
  memory_cap = capacity;
  std::cout << "MyString const with capacity called" << std::endl;
};
MyString::MyString(char c) {
  str = new char[1];
  str[0] = c;
  str_len = 1;
  memory_cap = 1;
  std::cout << "MyString const with char called" << std::endl;
}
MyString::MyString(const char *s) {
  str_len = strlen(s);
  memory_cap = str_len;
  str = new char[str_len];
  for (int i = 0; i != str_len; i++) {
    str[i] = s[i];
  }
}
MyString::MyString(const MyString &o) {
  std::cout << "복사 생성자 호출" << std::endl;
  str_len = o.str_len;
  memory_cap = str_len;
  str = new char[str_len];
  for (int i = 0; i != str_len; i++) {
    str[i] = o.str[i];
  }
}
MyString::~MyString() { delete[] str; }
int MyString::length() const { return str_len; }
void MyString::print() const {
  for (int i = 0; i != str_len; i++)
    std::cout << str[i];
}
void MyString::println() const {
  for (int i = 0; i != str_len; i++) {
    std::cout << str[i];
  }
  std::cout << ", length = " << this->length() << std::endl;
}
MyString &MyString::assign(const char *s) {
  int s_len = strlen(s);
  if (s_len > memory_cap) {
    delete[] str;
    str = new char[s_len];
    memory_cap = s_len;
  }
  for (int i = 0; i != s_len; i++)
    str[i] = s[i];
  str_len = s_len;
  return *this;
}
MyString &MyString::assign(const MyString &o) {
  if (o.str_len > memory_cap) {
    delete[] str;
    str = new char[o.str_len];
    memory_cap = o.str_len;
  }
  for (int i = 0; i != o.str_len; i++)
    str[i] = o.str[i];
  str_len = o.str_len + 1;
  return *this;
};
int MyString::capacity() const { return memory_cap; };
void MyString::reserve(int size) {
  if (size > memory_cap) {
    char *prev_string_content = str;
    str = new char[size];
    memory_cap = size;
    for (int i = 0; i != str_len; i++)
      str[i] = prev_string_content[i];
    delete[] prev_string_content;
  }
};
char MyString::at(int i) const {
  if (i < 0 || i >= str_len)
    return '\0';
  else
    return str[i];
};
MyString &MyString::insert(int loc, const MyString &o) {
  if (loc < 0 || loc > str_len)
    return *this;
  int new_str_len = str_len + o.str_len;
  if (new_str_len > memory_cap) {
    if (memory_cap * 2 > new_str_len)
      memory_cap *= 2;
    else
      memory_cap = new_str_len;
    char *prev_str_content = str;
    str = new char[new_str_len];
    int i;
    for (i = 0; i < loc; i++) {
      str[i] = prev_str_content[i];
    }
    for (int j = 0; j != o.str_len; j++) {
      str[i + j] = o.str[j];
    }
    for (; i < str_len; i++)
      str[o.str_len + i] = prev_str_content[i];
    delete[] prev_str_content;
    str_len = new_str_len;
    return *this;
  }
  for (int i = str_len - 1; i >= loc; i--) {
    str[i + o.str_len] = str[i];
  }
  for (int i = 0; i < o.str_len; i++) {
    str[i + loc] = o.str[i];
  }
  str_len = new_str_len;
  return *this;
};
MyString &MyString::insert(int loc, const char *s) {
  MyString temp(s);
  insert(loc, temp);
  return *this;
};
MyString &MyString::insert(int loc, char c) {
  MyString temp(c);
  insert(loc, temp);
  return *this;
};
MyString &MyString::erase(int loc, int num) {
  if (num < 0 || loc < 0 || loc > str_len)
    return *this;
  for (int i = loc + num; i < str_len; i++)
    str[i - num] = str[i];
  str_len -= num;
  return *this;
};

int MyString::find(int find_from, MyString &o) const {
  int i, j;
  if (o.str_len == 0)
    return -1;
  for (i = find_from; i <= str_len - o.str_len; i++) {
    for (j = 0; j < o.str_len; j++) {
      if (str[i + j] != o.str[j])
        break;
    }
    if (j == o.str_len)
      return i;
  }
  return -1;
};
int MyString::find(int find_from, const char *s) const {
  MyString temp(s);
  return find(find_from, temp);
};
int MyString::find(int find_from, char c) const {
  MyString temp(c);
  return find(find_from, temp);
};
int MyString::compare(const MyString &o) const {
  for (int i = 0; i < std::min(str_len, o.str_len); i++) {
    if (str[i] > o.str[i])
      return 1;
    else if (str[i] < o.str[i])
      return -1;
  }
  if (str_len == o.str_len)
    return 0;
  else if (str_len > o.str_len)
    return 1;
  return -1;
};
bool MyString::operator==(MyString &o) {
  if (this->compare(o) == 0)
    return true;
  return false;
};
void testexplicit(MyString s) { s.println(); };
char &MyString::operator[](const int index) { return str[index]; };
int main() {

  MyString str1("very very very long string");
  str1.reserve(30);
  std::cout << "Capacity : " << str1.capacity() << std::endl;
  std::cout << "String length : " << str1.length() << std::endl;
  str1.println();
  str1.assign("short string");
  std::cout << "Capacity : " << str1.capacity() << std::endl;
  std::cout << "String length : " << str1.length() << std::endl;
  str1.println();
  str1.assign("very long string");
  std::cout << "Capacity : " << str1.capacity() << std::endl;
  std::cout << "String length : " << str1.length() << std::endl;
  str1.println();
  str1.assign("very very very very very long string");
  std::cout << "Capacity : " << str1.capacity() << std::endl;
  std::cout << "String length : " << str1.length() << std::endl;
  str1.println();
  std::cout << "2th char : " << str1.at(2) << std::endl;
  str1.assign("very very very very very long string");
  str1.insert(1, 'c');
  str1.println();
  std::cout << "memory cap : " << str1.capacity() << std::endl;
  str1.insert(1, "hello");
  std::cout << "memory cap : " << str1.capacity() << std::endl;
  str1.println();
  str1.erase(1, 3);
  str1.println();
  std::cout << "find first very : " << str1.find(0, "very") << std::endl;
  std::cout << "find second very : "
            << str1.find(str1.find(0, "very") + 1, "very") << std::endl;
  MyString str2("abcdef");
  MyString str3("abcde");
  std::cout << "str2 and str3 compare : " << str1.compare(str2) << std::endl;
  // explicit
  // error below
  // testexplicit(3);

  if (str2 == str2)
    std::cout << "compare str2 with str2 with operator overloading : true"
              << std::endl;
  // [] overloading
  MyString str4("abcdef");
  str4[3] = 'c';
  str4.println();
}
