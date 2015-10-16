/* Első körben csináltam a bin helyett egy enum-ot, de szerintem
 * fölösleges ehhez a feladathoz, úgyhogy inkább írtam helyette
 * egy szép kis define... :D
*/

#include <iostream>
#include <bitset>

#define bin base(2)

class Printer
{
    public:
        Printer (std::ostream& os, int base) :
            os(os), base{base} {}

        std::ostream& operator<< (int a)
        {
            os << convert(a, base);
            return os;
        }

    private:
        std::ostream& os;
        int base;

        static std::string convert (int num, int base)
        {
            std::string out = "";
            int denom = biggest_div(num, base);

            while(denom != 0)
            {
                int cnt = num / denom;
                out += convert_to_char(cnt);
                num -= cnt * denom;
                denom /= base;
            }

            return out;
        }

        static int biggest_div (int num, int base)
        {
            int pow = base;
            while(pow <= num)
                pow *= base;

            return pow / base;
        }

        static char convert_to_char (int digit)
        {
            if (digit <= 9) return '0' + digit;
            return 'A' + digit - 10;
        }
};

class base
{
    public:
        base(int a) : _base{a} {}
        int get_base() { return _base; }
    private:
        int _base;
};


Printer operator<< (std::ostream& os, base b)
{
    return Printer{os, b.get_base()};
}

int main()
{
    std::cout << base(2) << 240 << std::endl;
    std::cout << base(8) << 240 << std::endl;
    std::cout << base(16) << 240 << std::endl;

    return 0;
}
