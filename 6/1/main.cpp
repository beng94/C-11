#include <new>
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <memory>

int cnt = 0;

void memleak()
{
    if (cnt == 0)
        std::cout << "No leaks detected\n";

    else
        std::cout << cnt << " leaks detected\n";
}

void* operator new(size_t size)
{
    if (size > 1024*1024*8)
        throw std::bad_alloc();
    void* ptr = malloc(size);
    if (ptr == NULL)
        throw std::bad_alloc();
    cnt++;
    std::cout << "allocated memory " << size << " bytes at " << ptr << std::endl;

    return ptr;
}

void operator delete(void* ptr) noexcept
{
    free(ptr);
    cnt--;
    std::cout << "freed memory at " << ptr << std::endl;
}


int main()
{
    atexit(memleak);

    ::operator new (sizeof(int) * 10000);
    return 0;
}
