#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

std::atomic ready(false);

void wait_for_ready()
{
    while (!ready.load())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "Thread " << std::this_thread::get_id() << " proceeding\n";
}

void set_ready()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));

    ready.store(true);

    std::cout << "Ready set to true\n";
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
