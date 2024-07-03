#include <iostream>
#include <string>
#include <thread>

void print_string(const std::string& s)
{
    std::cout << s << '\n';
}

class Animal
{
public:
    void operator()(const std::string& s) const
    {
        std::cout << "Hello, " << s << '\n';
    }
};

int main()
{
    // 1. Function Pointer
    std::thread t1(print_string, std::string("Hello, World"));

    // 2. Lambda Function
    std::thread t2(
        [](const std::string& name) { std::cout << "Hello, " << name << '\n'; },
        std::string("C++ Korea"));

    // 3. Functor
    std::thread t3(Animal(), std::string("Rabbit"));

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
