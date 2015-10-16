#include <cmath>
#include <iostream>

class Float
{
    private:
        float f;
        constexpr static double eps = 0.0001;
    public:
        Float(float f) : f{f} {}
        float get_f() const { return f; }
        double get_eps() const { return eps; }
};

Float operator- (const Float& lhs, const Float& rhs)
{
    return Float(lhs.get_f() - rhs.get_f());
}

Float operator-= (Float& lhs, const Float& rhs)
{
    lhs = Float(lhs - rhs);
}

Float operator+ (const Float& lhs, const Float& rhs)
{
    return Float(lhs.get_f() + rhs.get_f());
}

Float operator+= (Float& lhs, const Float& rhs)
{
    lhs = Float(lhs + rhs);
}

bool operator== (const Float& lhs, const Float& rhs)
{
    return std::fabs((lhs-rhs).get_f()) <= lhs.get_eps();
}

bool operator< (const Float& lhs, const Float& rhs)
{
    return (lhs.get_f() + 2*lhs.get_eps()) < rhs.get_f();
}

std::ostream& operator<< (std::ostream& os, const Float& f)
{
    os << f.get_f();
    return os;
}

int main()
{
    Float f1 = 1.0f;
    Float f2 = 1.00001f;
    Float f3 = 100;

    std::cout << (f1 < f2) << std::endl;
    std::cout << (f1 < f3) << std::endl;
    std::cout << (f1 == f2) << std::endl;

    for(Float f = 0.999; f < 1.001; f += 0.0001)
    {
        std::cout << f << '\t'<< (f < 1.0) << std::endl;
    }

    return 0;
}
