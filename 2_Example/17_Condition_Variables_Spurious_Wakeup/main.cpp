#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

bool ready = false;
std::mutex mtx;
std::condition_variable cv;

void wait_for_ready()
{
    std::unique_lock lock(mtx);

    while (!ready)
    {
        cv.wait(lock);
    }

    std::cout << "Thread proceeding after ready is true.\n";
}

void set_ready()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard lock(mtx);
        ready = true;
    }

    cv.notify_all();
}

int main()
{
    std::thread t1(wait_for_ready);
    std::thread t2(wait_for_ready);
    std::thread t3(set_ready);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
