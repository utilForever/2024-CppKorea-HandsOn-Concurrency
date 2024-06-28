#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

int counter = 0;
std::timed_mutex timed_mtx;

/*
    - Timed mutex
    - You can lock for a specified amount of time with
      try_lock_for() and try_lock_until()
*/

void increment()
{
    while (true)
    {
        if (timed_mtx.try_lock_for(std::chrono::milliseconds(100)))
        {
            ++counter;

            // Simulate work
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            timed_mtx.unlock();
            break;
        }
        else
        {
            std::cout << "Thread " << std::this_thread::get_id()
                      << " timed out\n";
        }
    }
}

int main()
{
    std::vector<std::thread> threads;
    threads.reserve(10);

    for (int i = 0; i < 10; ++i)
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
