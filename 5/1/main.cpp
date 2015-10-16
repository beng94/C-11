#include <cmath>
#include <iostream>

class Heron
{
    private:
        double x;

        bool good_enough (double guess)
        {
            return std::fabs(guess*guess - this->x) < 0.0001;
        }

        double improve (double guess)
        {
            return (guess + this->x / guess) / 2.0;
        }

    public:
        double get (double x)
        {
            this->x = x;

            double guess = 1.0;
            while(!good_enough(guess))
            {
                guess = improve(guess);
            }

            return guess;
        }
};

int main()
{
    Heron h;
    std::cout << h.get(2.0) << std::endl;

    return 0;
}
