#include <memory>
#include <iostream>

template <typename T>
class Stack
{
  private:
    T* stack;
    int last_id = -1;

  public:
    Stack(int size)
    {
        this->stack = (T*)malloc(sizeof(T) * size);
    }

    void push(T& item)
    {
        new (&stack[++last_id]) T{item};
    }

    T pop()
    {
        T tmp {stack[last_id]};
        stack[last_id--].~T();

        return tmp;
    }

    ~Stack()
    {
        for(int i = 0; i < last_id; i++)
            stack[i].~T();

        free(this->stack);
    }

    void operator= (const Stack&) = delete;
};

class Noisy {
public:
    explicit Noisy(int i) : i_{i} {
        std::cout << "Noisy{" << i << "} ctor\n"; count++;
    }
    Noisy(Noisy const &o) : i_{o.i_} {
        std::cout << "Noisy copy ctor " << i_ << "\n"; count++;
    }
    Noisy& operator=(Noisy const &o) = delete;
    ~Noisy() {
        std::cout << "Noisy dtor " << i_ << "\n"; count--;
    }
    void report() {
        std::cout << i_ << "\n";
    }
private:
    int i_;
    static int count;
};

int Noisy::count = 0;

int main()
{
    Stack<Noisy> s(5);

    Noisy *n = new Noisy(2);
    s.push(*n);

    s.pop().report();

    delete n;

    return 0;
}
