#include <atomic>
#include <iostream>
#include <memory>
#include <thread>

std::atomic<int*> ptr(nullptr);

void producer()
{
    int* p = new int(42);
    ptr.store(p);
}

void consumer()
{
    while (ptr.load() == nullptr)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    int* p = ptr.load();
    std::cout << "Consumed value: " << *p << '\n';

    delete p;
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
