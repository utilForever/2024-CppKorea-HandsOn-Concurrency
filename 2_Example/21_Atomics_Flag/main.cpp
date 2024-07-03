#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic_flag lock = ATOMIC_FLAG_INIT;

void work(int id)
{
    while (lock.test_and_set(std::memory_order_acquire))
    {
        // Busy-wait
    }

    std::cout << "Thread " << id << " acquired the lock\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Thread " << id << " releasing the lock\n";

    lock.clear(std::memory_order_release);
}

int main()
{
    std::vector<std::thread> threads;
    threads.reserve(5);

    // Create 5 threads
    for (int i = 0; i < 5; ++i)
    {
        threads.emplace_back(work, i);
    }

    for (auto& t : threads)
    {
        t.join();
    }

    return 0;
}
