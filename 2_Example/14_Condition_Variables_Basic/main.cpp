#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

bool done = false;
std::queue<int> queue;

std::mutex mtx;
std::condition_variable cv;

void producer()
{
    for (int i = 0; i < 10; ++i)
    {
        std::unique_lock lock(mtx);

        queue.push(i);

        std::cout << "Produced: " << i << '\n';
        cv.notify_one();
    }

    std::unique_lock lock(mtx);

    done = true;
    cv.notify_one();
}

void consumer()
{
    while (true)
    {
        std::unique_lock lock(mtx);
        cv.wait(lock, [] { return !queue.empty() || done; });

        while (!queue.empty())
        {
            int data = queue.front();
            queue.pop();

            std::cout << "Consumed: " << data << '\n';
        }

        if (done && queue.empty())
        {
            break;
        }
    }
}

int main()
{
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}
