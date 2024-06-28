#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    // 1. The maximum number of active threads
    std::cout << "The maximum number of active thread is "
              << std::thread::hardware_concurrency() << ".\n";

    // 2. Get the ID of the thread
    std::cout << "The ID of the thread is " << std::this_thread::get_id()
              << ".\n";

    // 3. Pause execution and give priority to other threads
    std::this_thread::yield();

    // 4. Sleep for some amount of time
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // 5. Sleep until some time
    auto time_point =
        std::chrono::system_clock::now() + std::chrono::seconds(5);

    std::this_thread::sleep_until(time_point);

    return 0;
}
