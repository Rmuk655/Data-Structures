#include "Rational.h"
#include <iostream>
Rational::Rational(int a, int b)
{
    if (b == 0)
    {
        throw std::invalid_argument("Denominator cannot be zero.");
    }
    numerator = a;
    denominator = b;
    reduce();
}

int Rational::gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}
void Rational::reduce()
{
    int g = gcd(numerator, denominator);
    numerator /= g;
    denominator /= g;
    if (denominator < 0) // Ensure denominator is positive
    {
        numerator = -numerator;
        denominator = -denominator;
    }
}
Rational Rational::add(const Rational &a, const Rational &b) const
{
    int c1 = b.numerator * a.denominator + a.numerator * b.denominator;
    int c2 = a.denominator * b.denominator;
    Rational c = Rational(c1, c2);
    return c;
}
Rational Rational::operator+(const Rational &other) const
{
    return add(*this, const_cast<Rational &>(other));
}
Rational Rational::subtract(const Rational &a, const Rational &b) const
{
    int c1 = a.numerator * b.denominator - b.numerator * a.denominator;
    int c2 = a.denominator * b.denominator;
    Rational c = Rational(c1, c2);
    return c;
}
Rational Rational::operator-(const Rational &other) const
{
    return Rational::subtract(*this, other);
}
Rational Rational::multiply(const Rational &a, const Rational &b) const
{
    int c1 = a.numerator * b.numerator;
    int c2 = a.denominator * b.denominator;
    Rational c = Rational(c1, c2);
    return c;
}
Rational Rational::operator*(const Rational &other) const
{
    return Rational::multiply(*this, other);
}
Rational Rational::divide(const Rational &a, const Rational &b) const
{
    int c1 = a.numerator * b.denominator;
    int c2 = a.denominator * b.numerator;
    if (c2 == 0)
    {
        throw std::invalid_argument("Division by zero.");
    }
    Rational c = Rational(c1, c2);
    return c;
}
Rational Rational::operator/(const Rational &other) const
{
    return Rational::divide(*this, other);
}
int Rational::getNumerator() const
{
    return numerator;
}
int Rational::getDenominator() const
{
    return denominator;
}
int Rational::setNumerator(int numerator)
{
    this->numerator = numerator;
    reduce(); // Reduce the fraction after setting the numerator
    return this->numerator;
}
int Rational::setDenominator(int denominator)
{
    if (denominator == 0)
    {
        throw std::invalid_argument("Denominator cannot be zero.");
    }
    this->denominator = denominator;
    reduce(); // Reduce the fraction after setting the denominator
    return this->denominator;
}
std::ostream &operator<<(std::ostream &os, const Rational &r)
{
    if (r.denominator == 1) // Handle whole number case
    {
        os << r.getNumerator();
        return os;
    }
    else if (r.denominator == -1)
    {
        os << -r.getNumerator(); // Handle negative whole number case
        return os;
    }
    os << r.getNumerator() << '/' << r.getDenominator();
    return os;
}

std::istream &operator>>(std::istream &is, Rational &r)
{
    char slash;
    int numerator, denominator;
    is >> numerator >> slash >> denominator;
    r.setNumerator(numerator);
    r.setDenominator(denominator);
    return is;
}
