#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

bool ready = false;
std::mutex mtx;
std::condition_variable cv;

void print_id(int id)
{
    std::unique_lock lock(mtx);
    cv.wait(lock, [] { return ready; });

    std::cout << "Thread " << id << '\n';
}

void set_ready_to_go()
{
    std::unique_lock lock(mtx);

    ready = true;
    cv.notify_all();
}

int main()
{
    std::thread threads[10];

    for (int i = 0; i < 10; ++i)
    {
        threads[i] = std::thread(print_id, i);
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    set_ready_to_go();

    for (auto& t : threads)
    {
        t.join();
    }

    return 0;
}
