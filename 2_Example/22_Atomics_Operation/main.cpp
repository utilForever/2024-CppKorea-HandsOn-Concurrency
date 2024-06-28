#include <atomic>
#include <iostream>
#include <thread>

std::atomic counter(0);

void increment()
{
    for (int i = 0; i < 1000; ++i)
    {
        // Atomic fetch and add
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

void decrement()
{
    for (int i = 0; i < 1000; ++i)
    {
        // Atomic fetch and subtract
        counter.fetch_sub(1, std::memory_order_relaxed);
    }
}

void exchange()
{
    // Atomic exchange
    int oldValue = counter.exchange(10, std::memory_order_relaxed);
    std::cout << "Exchanged old value: " << oldValue << " with new value: 10\n";
}

void compare_exchange()
{
    int expected = 10;

    if (counter.compare_exchange_strong(expected, 20,
                                        std::memory_order_relaxed))
    {
        std::cout << "Compare exchange succeeded, new value: " << counter.load()
                  << "\n";
    }
    else
    {
        std::cout << "Compare exchange failed, expected: " << expected
                  << ", actual: " << counter.load() << "\n";
    }
}

int main()
{
    std::thread t1(increment);
    std::thread t2(decrement);
    std::thread t3(exchange);
    std::thread t4(compare_exchange);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "Final counter value: " << counter.load() << '\n';
    return 0;
}
