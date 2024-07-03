#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>

// Shared data
int counter = 0;
// Mutex for critical section
std::shared_mutex shared_mtx;

/*
    A shared lock is just like a unique lock,
    except the lock is a shared lock as opposed to an exclusive one
    - Just like the normal lock guard, except...
    - It initializes a shared lock
    - It can be returned from the function without releasing the lock
      (via move semantics)
    - It can be released before it is destroyed
    - You can also use nifty lock methods!
*/

void reader()
{
    std::shared_lock lock(shared_mtx);
    std::cout << counter << '\n';
}

void writer()
{
    std::unique_lock lock(shared_mtx);
    ++counter;
}

int main()
{
    std::vector<std::thread> threads;
    threads.reserve(10);

    // Create writer and reader threads
    for (int i = 0; i < 5; ++i)
    {
        threads.emplace_back(writer);
        threads.emplace_back(reader);
    }

    for (auto& t : threads)
    {
        t.join();
    }

    return 0;
}
