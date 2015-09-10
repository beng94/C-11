#include <iostream>
#include <cassert>

class Fraction
{
    private:
        int count;
        int denom;

    public:
        Fraction(int, int);

        int get_count() const { return count; }
        int get_denom() const { return denom; }

        operator double() const;
};

Fraction operator+ (const Fraction& lhs);
Fraction operator+ (const Fraction& lhs, const Fraction& rhs);
Fraction& operator+= (Fraction& lhs, const Fraction& rhs);
Fraction operator- (const Fraction& lhs);
Fraction operator- (const Fraction& lhs, const Fraction& rhs);
Fraction& operator-= (Fraction& lhs, const Fraction& rhs);
Fraction operator* (const Fraction& lhs, const Fraction& rhs);
Fraction& operator*= (Fraction& lhs, const Fraction& rhs);
Fraction operator/ (const Fraction& lhs, const Fraction& rhs);
Fraction&  operator/= (Fraction& lhs, const Fraction& rhs);
std::istream& operator>> (std::istream& is, Fraction& rhs);

//Just for debugging
std::ostream& operator<< (std::ostream& os, const Fraction& rhs);

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
    return Fraction(
            lhs.get_count() * rhs.get_denom() + rhs.get_count() * lhs.get_denom(),
            lhs.get_denom() * rhs.get_denom()
            );
}

Fraction& operator+= (Fraction& lhs, const Fraction& rhs)
{
    return (lhs = lhs + rhs);
}

Fraction operator- (const Fraction& lhs)
{
    return Fraction(-lhs.get_count(), lhs.get_denom());
}

Fraction operator- (const Fraction& lhs, const Fraction& rhs)
{
    return lhs + (-rhs);
}

Fraction& operator-= (Fraction& lhs, const Fraction& rhs)
{
    return (lhs = lhs - rhs);
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
    return (lhs = lhs * rhs);
}

Fraction operator/ (const Fraction& lhs, const Fraction& rhs)
{
    return Fraction(
            lhs.get_count() * rhs.get_denom(),
            lhs.get_denom() * rhs.get_count()
            );
}

Fraction& operator/= (Fraction& lhs, const Fraction& rhs)
{
    return (lhs = lhs / rhs);
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

int main()
{
    Fraction ctor(10, 5);
    assert(ctor.get_count() == 2 && ctor.get_denom() == 1);

    Fraction plus_1 = +ctor;
    assert(plus_1.get_count() == 2 && plus_1.get_denom() == 1);

    Fraction plus_2 = ctor + ctor;
    assert(plus_2.get_count() == 4 && plus_2.get_denom() == 1);

    Fraction plus_equals(1, 1);
    plus_equals += ctor;
    assert(plus_equals.get_count() == 3 && plus_equals.get_denom() == 1);

    Fraction min_1 = -ctor;
    assert(min_1.get_count() == -2 && min_1.get_denom() == 1);

    Fraction min_2 = ctor - ctor;
    assert(min_2.get_count() == 0 && min_2.get_denom() == 1);

    Fraction min_equals(5, 1);
    min_equals -= ctor;
    assert(min_equals.get_count() == 3 && min_equals.get_denom() == 1);

    Fraction mult = ctor * ctor;
    assert(mult.get_count() == 4 && mult.get_denom() == 1);

    Fraction mult_equals(2, 1);
    mult_equals *= ctor;
    assert(mult_equals.get_count() == 4 && mult_equals.get_denom() == 1);

    Fraction div = ctor / ctor;
    assert(div.get_count() == 1 && div.get_denom() == 1);

    Fraction div_equals(2, 1);
    div_equals /= ctor;
    assert(div_equals.get_count() == 1 && div_equals.get_denom() == 1);

    Fraction input(1,1);
    std::cout << "Type in your input to test operator<<:" << std::endl;
    std::cin >> input;
    std::cout << "stored value: " << input << std::endl;

    Fraction cst(5, 2);
    double cast = (double)cst;
    assert(cast == 2.5);

    return 0;
}
