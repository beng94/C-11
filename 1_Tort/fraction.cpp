#include <iostream>

#include "fraction.hpp"

static int calc_gcd (int a, int b)
{
    int tmp;
    while (b != 0)
        tmp = a%b, a = b, b = tmp;

    return a;
}

Fraction::Fraction (int count, int denom)
{
    int gcd = calc_gcd(count, denom);
    this->count = count / gcd;
    this->denom = denom / gcd;
}

Fraction operator+ (const Fraction& lhs)
{
    return lhs;
}

Fraction operator+ (const Fraction& lhs, const Fraction& rhs)
{
    //TODO: use .count and .denom
    return Fraction(
            lhs.get_count() * rhs.get_denom() + rhs.get_count() * lhs.get_denom(),
            lhs.get_denom() * rhs.get_denom()
            );
}

void operator+= (Fraction& lhs, const Fraction& rhs)
{
    lhs = lhs + rhs;
}

void Fraction::operator+= (const Fraction& rhs)
{
    //Error: *this += rhs;
    //(*this).operator+=(rhs);
    //operator+=(*this, rhs);
    *this = *this + rhs;
}

Fraction operator- (const Fraction& lhs)
{
    return Fraction(-lhs.get_count(), lhs.get_denom());
}

Fraction operator- (const Fraction& lhs, const Fraction& rhs)
{
    return lhs + (-rhs);
}

void operator-= (Fraction& lhs, const Fraction& rhs)
{
    lhs = lhs - rhs;
}

Fraction operator* (const Fraction& lhs, const Fraction& rhs)
{
    return Fraction(
            lhs.get_count() * rhs.get_count(),
            lhs.get_denom() * lhs.get_denom()
            );
}

Fraction& operator*= (Fraction& lhs, const Fraction& rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

Fraction operator/ (const Fraction& lhs, const Fraction& rhs)
{
    return Fraction(
            lhs.get_count() * rhs.get_denom(),
            lhs.get_denom() * rhs.get_count()
            );
}

void operator/= (Fraction& lhs, const Fraction& rhs)
{
    lhs = lhs / rhs;
}

std::istream& operator>> (std::istream& is, Fraction& rhs)
{
    int count, denom;
    is >> count >> denom;
    rhs = Fraction(count, denom);

    return is;
}

//Just for debugging
std::ostream& operator<< (std::ostream& os, const Fraction& rhs)
{
    os << rhs.get_count() << " " << rhs.get_denom();
    return os;
}

Fraction::operator double() const
{
    return (double)count / denom;
}

