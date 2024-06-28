#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// Shared data
int counter = 0;
// Mutex for critical section
std::mutex mtx;

/*
    - Just like the normal lock guard, except...
    - It initializes an exclusive lock
    - It can be returned from the function without releasing the lock
      (via move semantics)
    - It can be released before it is destroyed
    - You can also use nifty lock methods!
*/

/*
    - Nifty lock: Initialize the lock guard, but don't actually lock yet
      For example, std::unique_lock<std::mutex> guard(mtx, std::defer_lock);

    - Now you can do some of the following!
      guard.lock();             // Lock now!
      guard.try_lock();         // Won't block if it can't acquire
      guard.try_lock_for();     // Only for timed_mutexes
      guard.try_lock_until();   // Only for timed_mutexes
*/

void increment()
{
    for (int i = 0; i < 1000; ++i)
    {
        // Acquire lock
        std::unique_lock lock(mtx);

        // Critical section
        ++counter;

        // You can manually unlock if needed
        // lock.unlock();
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
