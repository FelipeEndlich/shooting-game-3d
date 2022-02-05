#pragma once

#include <chrono>

namespace game {
    class Clock {
        public:
            Clock();

            virtual ~Clock() = default;

            void start();

            float elapsed();

            void tick(double miliseconds);
        
        private:
            std::chrono::time_point<std::chrono::system_clock> start_time;
    };
}