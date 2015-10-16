#include <iostream>

class Base
{
public:
    Base* next = nullptr;
    Base* prev = nullptr;

    virtual void process(int) = 0;

    virtual ~Base()
    {
        delete next;
    }
};

class Dummy final : public Base
{
public:
    virtual void process(int num) override
    {
        next->process(num);
    }
};

class Sieve final : public Base
{
public:
    int prime;

    Sieve(int prime) : prime{prime} {}

    virtual void process(int num) override

    {
        if(num % prime != 0)
        {
            next->process(num);
        }
    }
};

class Bucket final : public Base
{
    virtual void process(int num) override
    {
        Sieve* sieve = new Sieve(num);
        sieve->next = this;
        sieve->prev = this->prev;

        this->prev->next = sieve;
        this->prev = sieve;

        std::cout << num << std::endl;
    }
};

int main()
{
    Dummy *d = new Dummy;
    Bucket *b = new Bucket();
    d->next = b;
    b->prev = d;

    for(int i = 2; i < 100; i++)
    {
        d->process(i);
    }

    delete d;

    return 0;
}
