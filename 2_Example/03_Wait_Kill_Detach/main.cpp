#include <chrono>
#include <iostream>
#include <string>
#include <thread>

int main()
{
    // 1. Wait
    std::thread t1(
        [](const std::string& name) { std::cout << "Hello, " << name << '\n'; },
        std::string("C++ Korea"));

    // Block and wait for thread to finish
    t1.join();

    std::thread t2(
        [](const std::string& name) {
            std::cout << "What's up " << name << '\n';
        },
        std::string("Hands-on"));

    // So you can check if a thread is joinable before calling join()
    if (t2.joinable())
    {
        t2.join();
    }

    // 2. Kill
    // Use return statement, not std::terminate()!
    std::thread t3([]() {
        std::cout << "1 + 2 = \n";
        return;
        std::cout << "3\n";
    });

    t3.join();

    // 3. Detach
    // Split it from the std::thread() object that manages it
    std::thread t4([]() {
        for (int i = 1; i <= 1000; ++i)
        {
            std::cout << i << '\n';
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    t4.detach();

    return 0;
}
