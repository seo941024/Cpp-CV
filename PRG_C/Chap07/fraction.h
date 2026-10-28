/**************************************************************
 * Fraction 클래스의 구조를 선언하는                        *
 * fraction.h 헤더 파일                                       *
 **************************************************************/
#ifndef FRACTION_H
#define FRACTION_H

class Fraction
{
private:
  // 멤버 변수 (속성)
  int numer;
  int denom;

  // 내부 전용 멤버 함수 (도우미 함수)
  void normalize();
  int gcd(int n, int m);

public:
  // 생성자와 소멸자
  Fraction();                      // 기본 생성자
  Fraction(int num, int den = 1);  // 매개변수가 있는 생성자
  Fraction(const Fraction &fract); // 복사 생성자
  ~Fraction();                     // 소멸자

  // 접근자 (Getters)
  int getNumer() const;
  int getDenom() const;
  void print() const;

  // 설정자 (Setters)
  void setNumer(int num);
  void setDenom(int den);
};

#endif // FRACTION_H