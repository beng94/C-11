#include <iostream>

class TimeInterval
{
    private:
        int min = 0;
    public:
        TimeInterval() = default;
        constexpr TimeInterval (int mins) : min{mins} {}

        int get_hour() const { return this->min / 60; }
        int get_min() const { return this->min % 60; }
};

std::ostream& operator<< (std::ostream& os, const TimeInterval& t)
{
    os << t.get_hour() << "h " << t.get_min() << 'm';
    return os;
}

constexpr TimeInterval operator "" _h (unsigned long long int hour)
{
    return TimeInterval(hour * 60);
}

constexpr TimeInterval operator "" _m (unsigned long long int min)
{
    return TimeInterval(min);
}

TimeInterval operator+ (const TimeInterval& lhs, const TimeInterval& rhs)
{
    int hours = lhs.get_hour() + rhs.get_hour();
    int mins = lhs.get_min() + rhs.get_min();
    return TimeInterval(hours * 60 + mins);
}

int main()
{
    TimeInterval i1{65};
    std::cout << i1 << std::endl;

    TimeInterval i2 = 5_h + 79_m;
    std::cout << i2 << std::endl;
}
