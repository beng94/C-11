#include <string.h>
#include <iostream>

int operator "" _binary(const char * str)
{
    int num = 0;
    int exp = 1;
    int len = strlen(str);
    for(int i = len -1; i >= 0; i--)
    {
        num += exp * (str[i] - '0');
        exp *= 2;
    }

    return num;
}

int main()
{
    std::cout << 1111_binary << std::endl;
    std::cout << 10000000_binary << std::endl;

    return 0;
}
