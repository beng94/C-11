#include <iostream>

class Fraction
{
    private:
        int count;
        int denom;

    public:
        Fraction(int, int);

        //TODO: consider using const
        Fraction operator+(const Fraction&);
        void operator+=(const Fraction&);
        Fraction operator-(const Fraction&);
        Fraction operator*(const Fraction&);
        Fraction operator/(const Fraction&);
        friend std::istream &operator>>(std::istream&, Fraction&);
        operator double() const;
};

static int calc_gcd(int a, int b)
{
    int tmp;
    while (b != 0)
        tmp = a%b, a = b, b = tmp;

    return a;
}

Fraction::Fraction(int count, int denom)
{
    int gcd = calc_gcd(count, denom);
    this->count = count / gcd;
    this->denom = denom / gcd;
}

Fraction Fraction::operator+(const Fraction& rhs)
{
    return Fraction(
            this->count * rhs.denom + rhs.count * this->denom,
            this->denom * rhs.denom);
}

void Fraction::operator+=(const Fraction& rhs)
{
    this->count = this->count * rhs.denom + rhs.count * this->denom;
    this->denom = this->denom * rhs.denom;
}

void operator+= (Fraction& lhs, const Fraction& rhs)
{
    lhs = lhs + rhs;
    //Error: lhs += rhs;
}

Fraction Fraction::operator-(const Fraction& rhs)
{
    return Fraction(
            this->count * rhs.denom - rhs.count * this->denom,
            this->denom * rhs.denom
            );
}

Fraction operator-(const Fraction& lhs, const Fraction& rhs)
{
    return lhs - rhs;
}

void operator-=(Fraction& lhs, const Fraction& rhs)
{
    lhs = lhs - rhs;
}

Fraction Fraction::operator*(const Fraction& rhs)
{
    return Fraction(
            this->count * rhs.count,
            this->denom * rhs.denom
            );
}

void operator*= (Fraction& lhs, const Fraction& rhs)
{
    lhs = lhs * rhs;
}

Fraction Fraction::operator/(const Fraction& rhs)
{
    return Fraction(
            this->count * rhs.denom,
            this->denom * rhs.count
            );
}

void operator/=(Fraction& lhs, const Fraction& rhs)
{
    lhs = lhs / rhs;
}

std::istream& operator>> (std::istream& is, Fraction& rhs)
{
    is >> rhs.count >> rhs.denom;
    //Error: is >> rhs.count >> '/' >> rhs.denom;
    return is;
}

Fraction::operator double() const
{
    return (double)this->count / this->denom;
}
