#include <stack>
#include <iostream>
#include <string>

int main()
{
    std::string line;
    std::cin >> line;

    std::stack<int> stack;
    for(char c: line)
    {
        switch (c)
        {
            case '+':
            {
                int a = stack.top();
                int b = stack.top();
                stack.push(a + b);
                break;
            }

            case '*':
            {
                int a = stack.top();
                int b = stack.top();
                stack.push(a * b);
                break;
            }

            default:
            {
                int b = std::stod("2");
                int c = std::stod('2');
                //int a = std::stod(std::string(c));
                //stack.push(a);
                break;
            }
        }

    }

    return 0;
}
