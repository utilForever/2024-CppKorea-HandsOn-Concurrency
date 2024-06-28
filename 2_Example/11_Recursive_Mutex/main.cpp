#include <iostream>
#include <mutex>
#include <thread>

int counter = 0;
std::recursive_mutex rec_mtx;

/*
    - Multiple locks can be acquired by the same thread
    - You need to call unlock the same amount of times you've called lock
      before the lock is released
*/

void increment(int depth)
{
    if (depth <= 0)
    {
        return;
    }

    rec_mtx.lock();

    ++counter;
    increment(depth - 1);

    rec_mtx.unlock();
}

int main()
{
    std::thread t1(increment, 10);
    std::thread t2(increment, 10);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter << '\n';

    return 0;
}
