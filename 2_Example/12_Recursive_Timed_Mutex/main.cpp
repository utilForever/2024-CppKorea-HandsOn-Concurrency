#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

int counter = 0;
std::recursive_timed_mutex rec_timed_mtx;

/*
    - Combines the functionality of std::recursive_mutex and std::timed_mutex,
      allowing recursive locking with timeout capabilities
*/

void increment(int depth)
{
    if (depth <= 0)
    {
        return;
    }

    if (rec_timed_mtx.try_lock_for(std::chrono::milliseconds(100)))
    {
        ++counter;
        increment(depth - 1);

        rec_timed_mtx.unlock();
    }
    else
    {
        std::cout << "Thread " << std::this_thread::get_id() << " timed out\n";
    }
}

int main()
{
    std::vector<std::thread> threads;
    threads.reserve(100);

    // Create 100 threads
    for (int i = 0; i < 100; ++i)
    {
        threads.emplace_back(increment, 10);
    }

    for (auto& t : threads)
    {
        t.join();
    }

    std::cout << "Final counter value: " << counter << '\n';

    return 0;
}
