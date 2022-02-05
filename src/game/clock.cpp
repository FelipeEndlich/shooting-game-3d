#include <chrono>
#include "./clock.hpp"

using game::Clock;

Clock::Clock() {
    this->start_time = std::chrono::system_clock::now();
}

void Clock::start() {
    this->start_time = std::chrono::system_clock::now();
}

float Clock::elapsed() {
    std::chrono::duration<double> elapsed_time;
    std::chrono::milliseconds duration_in_ms;

    elapsed_time = std::chrono::system_clock::now() - this->start_time;
    duration_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time);

    return duration_in_ms.count();
}

void Clock::tick(double miliseconds) {
    while (this->elapsed() < miliseconds)
        continue;
}