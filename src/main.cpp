#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>
#include <thread>
#include <cmath>
#include <vector>
#include <numeric>
#include <atomic>
#include "include/functions.h"

void primes_in_range(uint64_t lower_limit, uint64_t upper_limit);

std::atomic<unsigned int> prime_count = 0;

int main() {
    using namespace std::chrono_literals;
    int thread_count = std::thread::hardware_concurrency();
    switch (thread_count) {
        case 0:
            std::cout << "Implementation does not seem to support 'std::thread::hardware_concurrency()'." << '\n';
            std::exit(EXIT_FAILURE);
        case 1:
            std::cout << "System only suppports a single thread." << '\n';
            break;
        default:
            std::cout << "System supports " << thread_count << " threads." << '\n';
            break;
    }
    constexpr int repeat_val = 10;
    uint64_t iteration_length_arr[repeat_val];
    long double avg_search_time = 0.0;
    constexpr uint64_t lower_search_limit = 1;
    constexpr uint64_t upper_search_limit = 100000000;
    int remainder_range_start = 0;
    int remainder_range_end = 0;
    uint64_t start_of_range[thread_count] = {};
    uint64_t end_of_range[thread_count] = {};
    std::string choice;
    std::string yes_choices[] = {"Y", "y", "Yes", "yes"};
    std::string no_choices[] = {"N", "n", "No", "no"};
    
    auto result = std::div(upper_search_limit, (long) thread_count);
    std::cout << "Numerator: " << upper_search_limit << '\n';
    std::cout << "Denominator (also how many threads): " << thread_count << '\n';
    std::cout << "Quotient: " << result.quot << '\n';
    std::cout << "Remainder: " << result.rem << '\n';
    std::cout << "  ****  " << '\n';
    
    //Calculating start and end vales for the ranges.
    for (int i = 0; i < thread_count; i++) {
        if (i == 0) {
            start_of_range[i] = lower_search_limit;
            end_of_range[i] = result.quot;
        } else {
            start_of_range[i] = end_of_range[i - 1] + 1;
            end_of_range[i] = (start_of_range[i] - 1) + result.quot;
        }
    }
    
    //Calculating start and end values for remainder range.
    if (result.rem != 0) {
        remainder_range_start = (upper_search_limit - result.rem) + 1;
        remainder_range_end = upper_search_limit;
    }

    std::cout << "Start prime_threads between " << lower_search_limit << " and " << upper_search_limit << "? [Y/n]: ";
    std::cin >> choice;
    if (std::find(std::begin(yes_choices), std::end(yes_choices), choice) != std::end(yes_choices)) {
        std::cout << "Starting multithreaded prime benchmark..." << '\n';
        auto prog_start_time = std::chrono::steady_clock::now();

        for (int k = 0; k < repeat_val; k++) {
            std::cout << "Iteration " << (k + 1) << " of " << repeat_val << " Runtime (ns): ";
            //Create vector to hold main thread objects.
            std::vector<std::thread> main_threads;

            auto iteration_start_time = std::chrono::steady_clock::now();
            //Create and start main threads.
            for (int i = 0; i < thread_count; i++) {
                main_threads.push_back(std::thread(primes_in_range, start_of_range[i], end_of_range[i]));
            }

            //Join main threads.
            for (auto &th : main_threads) {
                th.join();
            }

            //Create remainder thread (if needed).
            if (result.rem != 0) {
                std::thread remainder_thread = std::thread(primes_in_range, remainder_range_start, remainder_range_end);
                
                remainder_thread.join();
            }
            auto iteration_stop_time = std::chrono::steady_clock::now();
            std::chrono::duration<uint64_t, std::nano> elapsed_single_iteration = iteration_stop_time - iteration_start_time; //how many nanoseconds have elapsed.
            iteration_length_arr[k] = elapsed_single_iteration.count(); //store elapsed_single_iteration nanoseconds in iteration_length_arr.
            std::cout << elapsed_single_iteration.count() << '\n';
        }

        avg_search_time = std::accumulate(std::begin(iteration_length_arr), std::end(iteration_length_arr), avg_search_time) / repeat_val;

        auto prog_stop_time = std::chrono::steady_clock::now();
        std::chrono::duration<uint64_t, std::nano> elapsed_prog_runtime = prog_stop_time - prog_start_time; //how many nanoseconds have elapsed.
        uint64_t prog_runtime_nanoseconds = elapsed_prog_runtime.count();

        std::cout << "Prime benchmark is done!" << '\n';

        std::cout << "\n**** Results ****" << '\n';
        std::cout << "Program ran for total of (DD:HH:MM:SS.SSSSSSSSS): " << func::to_days_hours_minutes_seconds(prog_runtime_nanoseconds) << '\n';
        std::cout << "\n";
        std::cout << "Program ran for: " << prog_runtime_nanoseconds << " ns" << '\n';
        std::cout << "\n";
        std::cout << "Average time to find all primes between " << lower_search_limit << " and " << upper_search_limit << " was (DD:HH:MM:SS.SSSSSSSSS):" << '\n';
        std::cout << func::to_days_hours_minutes_seconds((uint64_t) avg_search_time) << '\n';
        std::cout << "\n";
        std::cout << "Average search time: " << (uint64_t) avg_search_time << " ns" << '\n';
        std::cout << "Number of primes found is: " << prime_count / repeat_val << '\n';
    } else if (std::find(std::begin(no_choices), std::end(no_choices), choice) != std::end(no_choices)) {
        std::cout << "Exited program." << '\n';
    } else if (!(std::find(std::begin(yes_choices), std::end(yes_choices), choice) != std::end(yes_choices)) && 
            !(std::find(std::begin(no_choices), std::end(no_choices), choice) != std::end(no_choices))) {
        std::cout << "Command not valid; please restart program and try again." << '\n';
    }
    
    return 0;
}

void primes_in_range(uint64_t lower_limit, uint64_t upper_limit) {
    unsigned int count = 0;
    for (uint64_t i = lower_limit; i < upper_limit + 1; i++) {
        if (func::prime::is_prime(i)) {
            count++;
        }
    }

    prime_count += count;
}
