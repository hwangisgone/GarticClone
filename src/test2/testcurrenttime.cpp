#include <iostream>
#include <chrono>
#include <ctime>

int main() {
    auto current_time = std::chrono::system_clock::now();
    std::time_t time_now = std::chrono::system_clock::to_time_t(current_time);
    int seconds_since_epoch = static_cast<int>(time_now);
    std::cout << "Current time in seconds since epoch: " << seconds_since_epoch << std::endl;
    return 0;
}