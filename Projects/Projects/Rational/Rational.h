#include <iostream>
class Rational
{
private:
    int numerator;
    int denominator;
    int gcd(int a, int b);
    void reduce();

public:
    Rational add(const Rational &a, const Rational &b) const;
    Rational operator+(const Rational &other) const;
    Rational subtract(const Rational &a, const Rational &b) const;
    Rational operator-(const Rational &other) const;
    Rational multiply(const Rational &a, const Rational &b) const;
    Rational operator*(const Rational &other) const;
    Rational divide(const Rational &a, const Rational &b) const;
    Rational operator/(const Rational &other) const;
    Rational(int a, int b);
    int getNumerator() const;
    int getDenominator() const;
    int setNumerator(int numerator);
    int setDenominator(int denominator);
    friend std::ostream &operator<<(std::ostream &os, const Rational &r);
    friend std::istream &operator>>(std::istream &is, Rational &r);
};