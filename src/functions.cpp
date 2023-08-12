#include "include/functions.h"
#include <iostream>
#include <cmath>
#include <string>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <stdexcept>

namespace func {

    namespace prime {

        bool is_prime(int64_t n) {
            //Checks if a single signed 64-bit integer is a prime number.
            if (n > std::numeric_limits<int64_t>::max() || n < std::numeric_limits<int64_t>::min()) {
                throw std::invalid_argument("Argument 'n' is out of range for 'int64_t' type.");
            }
            if (n <= 1) {
                return false;
            } else if (n == 2) {
                return true;
            } else if (n > 2 && n % 2 == 0) {
                return false;
            }

            int64_t max_divisor = std::ceil(std::sqrt((long double) n));
            for (int64_t d = 3; d < max_divisor + 1; d+=2) {
                if (n % d == 0) {
                    return false;
                }
            }

            return true;
        }
    }

    std::string to_days_hours_minutes_seconds(uint64_t nanoseconds) {
        /*Converts an unsigned 64-bit integer representing nanoseconds to a std::string that
        equals the number of days, hours, minutes, seconds and fractions of a second said value converts to.*/
        if (nanoseconds > std::numeric_limits<uint64_t>::max() || nanoseconds < std::numeric_limits<uint64_t>::min()) {
            throw std::invalid_argument("Argument 'nanoseconds' is out of range for 'uint64_t' type.");
        }
        constexpr uint64_t ns_in_day = 86400000000000;
        constexpr uint64_t ns_in_hour = 3600000000000;
        constexpr uint64_t ns_in_min = 60000000000;
    
        auto days = nanoseconds / ns_in_day;
        nanoseconds = nanoseconds - (days * ns_in_day);
    
        auto hours = nanoseconds / ns_in_hour;
        nanoseconds = nanoseconds - (hours * ns_in_hour);
    
        auto minutes = nanoseconds / ns_in_min;
        nanoseconds = nanoseconds - (minutes * ns_in_min);
    
        auto seconds = nanoseconds / 1000000000;
        nanoseconds = nanoseconds - (seconds * 1000000000);
    
        auto nanosecs = nanoseconds;
    
        try {
            return zero_padded_num(std::to_string(days), 2) + ":" +
            zero_padded_num(std::to_string(hours), 2) + ":" +
            zero_padded_num(std::to_string(minutes), 2) + ":" +
            zero_padded_num(std::to_string(seconds), 2) + "." +
            zero_padded_num(std::to_string(nanosecs), 9);
        } catch (std::invalid_argument const& ex) {
            std::cout << ex.what() << '\n';
        }

        return "";
    }

    std::string zero_padded_num(std::string str, size_t field_width) {
        //Takes a std::string representing an integer and zero-padds it to a given width to ensure a fixed width std::string as a result.
        if (field_width > std::numeric_limits<size_t>::max() || field_width < std::numeric_limits<size_t>::min()) {
            throw std::invalid_argument("Argument 'field_width' is out of range for 'size_t' type in this case.");
        }
        int precision = field_width - std::min(field_width, str.size());
        return std::string(precision, '0').append(str);
    }

    std::string to_UTC(std::chrono::system_clock::time_point now) {
        //Convert a system clock time point to UTC and return time as a std::string with format "yyyy-mm-dd hh:mm:ss".
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        char timeString[std::size("yyyy-mm-dd hh:mm:ss UTC")];
        std::strftime(std::data(timeString), std::size(timeString), "%F %T UTC", std::gmtime(&time));
        return timeString;
    }

    std::string replace_char(char target_char, char replacement_char, std::string target_str) {
        //Replace all occurrences of a given char in a std::string with another.
        if (target_char > std::numeric_limits<char>::max() || target_char < std::numeric_limits<char>::min()) {
            throw std::invalid_argument("Argument 'target_char' is out of range for 'char' type.");
        } else if (replacement_char > std::numeric_limits<char>::max() || replacement_char < std::numeric_limits<char>::min()) {
            throw std::invalid_argument("Argument 'target_char' is out of range for 'char' type.");
        }
        std::replace(target_str.begin(), target_str.end(), target_char, replacement_char);
        return target_str;
    }

}