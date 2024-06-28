#include <chrono>
#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>

int counter = 0;
std::shared_timed_mutex shared_timed_mtx;

/*
    - Read-Write mutex
    - Can acquire both exclusive or shared locks
      (just use the appropriate lock guard type!)
*/

void reader()
{
    while (true)
    {
        if (shared_timed_mtx.try_lock_shared_for(
                std::chrono::milliseconds(100)))
        {
            std::cout << "Reader " << std::this_thread::get_id() << ": "
                      << counter << '\n';

            shared_timed_mtx.unlock_shared();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            break;
        }
        else
        {
            std::cout << "Reader " << std::this_thread::get_id()
                      << " timed out\n"; 
        }
    }
}

void writer()
{
    while (true)
    {
        if (shared_timed_mtx.try_lock_for(std::chrono::milliseconds(100)))
        {
            ++counter;

            // Simulate work
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            shared_timed_mtx.unlock();

            break;
        }
        else
        {
            std::cout << "Writer " << std::this_thread::get_id()
                      << " timed out\n";
        }
    }
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