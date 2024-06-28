#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

bool ready = false;
std::mutex mtx;
std::condition_variable cv;

void wait()
{
    std::unique_lock lock(mtx);

    if (cv.wait_for(lock, std::chrono::seconds(2), [] { return ready; }))
    {
        std::cout << "Thread finished waiting, ready was true.\n";
    }
    else
    {
        std::cout << "Thread finished waiting, timeout occurred.\n";
    }
}

void signal()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard lock(mtx);
        ready = true;
    }

    cv.notify_one();
}

int main()
{
    std::thread t1(wait);
    std::thread t2(signal);

    t1.join();
    t2.join();

    return 0;
}
