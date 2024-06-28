#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int> counter(0);

void increment()
{
    for (int i = 0; i < 1000; ++i)
    {
        // Atomic increment
        ++counter;
    }
}

int main()
{
    std::vector<std::thread> threads;
    threads.reserve(10);

    // Create 10 threads
    for (int i = 0; i < 10; ++i)
    {
        threads.emplace_back(increment);
    }

    // Join all threads
    for (auto& t : threads)
    {
        t.join();
    }

    std::cout << "Final counter value: " << counter.load() << '\n';

    return 0;
}
