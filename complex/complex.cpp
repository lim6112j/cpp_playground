#include <cctype>
#include <iostream>
#include <cstring>
#include <ostream>
class Complex {
private:
  double real, img;
  double get_number( const char* str, int begin, int end);
public:
  Complex(double real, double img) : real(real), img(img) {}
  Complex(const Complex& c) {real = c.real, img = c.img;}
  Complex(const char* str) {
    int begin = 0, end = strlen(str);
    img = 0.0;
    real = 0.0;
    int pos_i = -1;
    for(int i = 0; i <= end; i++) {
      if(str[i] == 'i') {
	pos_i = i;
	break;
      }
    }
    if(pos_i == -1) {
      real = get_number(str, begin, pos_i - 1);
      return;
    }
    real = get_number(str, begin, pos_i - 1);
    img = get_number(str, pos_i + 1, end);
    if (pos_i >= 1 && str[pos_i - 1] == '-') img *= -1.0;
  };
  //Complex plus(const Complex& c);
  //Complex minus(const Complex& c);
  //Complex times(const Complex& c);
  //Complex divide(const Complex& c);

  // operator overloading
  //Complex operator+(const Complex& c) const; // ambiguous problem
  Complex operator+(const char *str) const; 
  Complex operator-(const Complex& c) const;
  Complex operator-(const char *str) const; 
  Complex operator*(const Complex& c) const;
  Complex operator*(const char* str) const;
  Complex operator/(const Complex& c) const;
  Complex operator/(const char* str) const;
  Complex& operator=(const Complex& c) ;
  void println() { std::cout << "( " << real << " , " << img << " )" << std::endl; }

  Complex& operator+=(const Complex& c);
  Complex& operator-=(const Complex& c);
  Complex& operator*=(const Complex& c);
  Complex& operator/=(const Complex& c);

  // 교환법칙
  friend Complex operator+(const Complex& a, const Complex& b);
  friend std::ostream& operator<<(std::ostream& os, const Complex& c); 
};

double Complex::get_number( const char* str, int from, int to) {
  bool minus = false;
  if ( from > to ) return 0;
  if (str[from] == '-') minus = true;
  if (str[from] == '-' || str[from] == '+') from++;
  double num = 0.0;
  double decimal = 1.0;
  bool integer_part = true;
  for( int i = from; i <= to; i++) {
    if(std::isdigit(str[i]) && integer_part) {
      num *= 10.0;
      num += (str[i] - '0');
    } else if(str[i] == '.') {
      integer_part = false;
    } else if(std::isdigit(str[i]) && !integer_part) {
      decimal /= 10.0;
      num += ((str[i] - '0') * decimal);
    } else break;
  }
  if(minus) num *= -1.0;
  return num;
};
// compare return type !!
// Complex& Complex::operator+(const Complex &c) const {}

//Complex Complex::operator+(const Complex &c) const {
//Complex temp(real + c.real, img + c.img);
//return temp;
//};
// 교환 법칙. ambiguous problem, comment above cstr
Complex operator+(const Complex &a, const Complex &b) {
  Complex temp(a.real + b.real, a.img + b.img);
  return temp;
};
Complex Complex::operator+(const char *str) const{
  //int begin = 0, end = strlen(str);
  //double str_img = 0.0, str_real = 0.0;
  //int pos_i = -1;
  //for (int i = 0; i != end; i++) {
  //if(str[i] == 'i') {
  //pos_i = i;
  //break;
  //}
  //}
  //if(pos_i == -1) {
  //str_real = get_number(str, begin, end - 1);
  //Complex temp(str_real, str_img);
  //return (*this) + temp;
  //}
  //str_real = get_number(str, begin, pos_i - 1);
  //str_img = get_number(str, pos_i + 1, end - 1);
  //if(pos_i >= 1 && str[pos_i - 1] == '-') str_img *= -1.0;
  //Complex temp(str_real, str_img);
  //return (*this) + temp;
  Complex temp(str);
  return (*this) + temp;
}
Complex Complex::operator-(const Complex &c) const {
  Complex temp(real - c.real, img - c.img);
  return temp;
};
Complex Complex::operator-(const char* str) const {
  Complex temp(str);
  return (*this) - temp;
}
Complex Complex::operator*(const Complex &c) const {
  Complex temp(real * c.real - img * c.img, real * c.img + img * c.real);
  return temp;
};
Complex Complex::operator*(const char *str) const {
  Complex temp(str);
  return (*this) * temp;
}
Complex Complex::operator/(const Complex &c) const {
  Complex temp((real * c.real + img * c.img) / (c.real * c.real + c.img * c.img),
	       (img * c.real - real * c.img) / (c.real * c.real + c.img * c.img));
  return temp;
};
Complex Complex::operator/(const char *str) const {
  Complex temp(str);
  return (*this) / temp;
}
Complex& Complex::operator=(const Complex &c) {
  real = c.real;
  img = c.img;
  return *this;  
};
Complex &Complex::operator+=(const Complex &c) {
  *this = *this + c;
  return *this;
};
Complex &Complex::operator-=(const Complex &c) {
  *this = *this - c;
  return *this;
};
Complex &Complex::operator*=(const Complex &c) {
  *this = *this * c;
  return *this;
};
Complex &Complex::operator/=(const Complex &c) {
  *this = *this / c;
  return *this;
};
std::ostream& operator<<(std::ostream& os, const Complex& c) {
  //std::cout << "customized << called" << std::endl;
  os << "( " << c.real << " , " << c.img << " )";
  return os;
}
int main() {
  Complex a (1.0, 2.0);
  Complex b (3.0, -2.0);
  Complex c = a * b;
  c.println();
  Complex d = a / b;
  d.println();
  Complex e (0.0, 0.0);
  e = a * b + a /b + a + b;
  e.println();
  Complex f(1.0, 2.0);
  Complex g(3.0, -2.0);
  a += b;
  a.println();
  b.println();
  // a + bj 와 같은 문자열 연산:
  Complex h(0,0);
  h = h + "-1.1 + i3.923";
  h.println();
  // str 을 받는 생성자 추가
  Complex i(0,0);
  i = i + "-1.1 + i3.923";
  i.println();
  i = i - "1.2 -i1.823";
  i.println();
  i = i * "2.3+i22";
  i.println();
  i = i / "-12+i55";
  i.println();
  //교환 법칙
  Complex j(0,0);
  j = "-1.1 + i3.923" + j;
  j.println();
  // << operator
  std::cout << "j value : " << j << std::endl;
}
