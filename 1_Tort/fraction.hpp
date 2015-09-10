#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>

class Fraction
{
    private:
        int count;
        int denom;

    public:
        Fraction(int, int);

        int get_count() const { return count; }
        int get_denom() const { return denom; }

        void operator+=(const Fraction&);
        operator double() const;
};

Fraction operator+ (const Fraction& lhs);
Fraction operator+ (const Fraction& lhs, const Fraction& rhs);
void operator+= (Fraction& lhs, const Fraction& rhs);
Fraction operator- (const Fraction& lhs);
Fraction operator- (const Fraction& lhs, const Fraction& rhs);
void operator-= (Fraction& lhs, const Fraction& rhs);
Fraction operator* (const Fraction& lhs, const Fraction& rhs);
Fraction& operator*= (Fraction& lhs, const Fraction& rhs);
Fraction operator/ (const Fraction& lhs, const Fraction& rhs);
void operator/= (Fraction& lhs, const Fraction& rhs);
std::istream& operator>> (std::istream& is, Fraction& rhs);

//Just for debugging
std::ostream& operator<< (std::ostream& os, const Fraction& rhs);

#endif
