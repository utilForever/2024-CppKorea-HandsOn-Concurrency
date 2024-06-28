#include <iostream>
#include <thread>
#include <vector>

// Shared data
int counter = 0;

void increment()
{
    for (int i = 0; i < 1000; ++i)
    {
        // Critical section
        ++counter;
    }
}

int main()
{
    std::vector<std::thread> threads;
    threads.reserve(1000);

    // Create 10 threads
    for (int i = 0; i < 1000; ++i)
    {
        threads.emplace_back(increment);
    }

    for (auto& t : threads)
    {
        t.join();
    }

    std::cout << "Final counter value: " << counter << '\n';

    return 0;
}
