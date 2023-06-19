#include <string>
#include <chrono>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

namespace func {
    
    namespace prime {
        bool is_prime(int64_t n);
    }

    std::string to_days_hours_minutes_seconds(uint64_t nanoseconds);
    std::string zero_padded_num(std::string str, size_t field_width);
    std::string to_UTC(std::chrono::system_clock::time_point now);
}

#endif