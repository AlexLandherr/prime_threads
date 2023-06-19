#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>
#include <thread>
#include <cmath>
#include <vector>
#include <numeric>
#include <atomic>
#include <array>
#include <ctime>
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
    std::cout << "    ****    " << '\n';

    constexpr int repeat_val = 10;
    std::array<long double, repeat_val> iteration_length_arr;
    long double avg_search_time = 0.0;
    constexpr uint64_t lower_search_limit = 1;
    constexpr uint64_t upper_search_limit = 100000000;
    int remainder_range_start = 0;
    int remainder_range_end = 0;
    std::vector<uint64_t> start_of_range = {};
    std::vector<uint64_t> end_of_range = {};
    std::string choice;
    std::array<std::string, 4> yes_choices = {"Y", "y", "Yes", "yes"};
    std::array<std::string, 4> no_choices = {"N", "n", "No", "no"};
    std::array<int, 3> valid_modes = {0, 1, 2};
    int mode_select = 0;

    std::chrono::_V2::steady_clock::time_point prog_start_time;
    std::chrono::_V2::steady_clock::time_point prog_stop_time;
    uint64_t prog_runtime_nanoseconds = 0;
    std::chrono::duration<uint64_t, std::nano> elapsed_prog_runtime;

    ldiv_t result;

    std::cout << "Search limit for all options are (both are inclusive limits):" << '\n';
    std::cout << "Lower search limit: " << lower_search_limit << '\n';
    std::cout << "Upper search limit: " << upper_search_limit << '\n';

    std::cout << '\n';
    
    while (true) {
        std::cout << "Select benchmark mode from list below:" << '\n';
        std::cout << "0. Single-threaded benchmark." << '\n';
        std::cout << "1. Multi-threaded benchmark (" << thread_count << " threads)." << '\n';
        std::cout << "2. Exit program." << '\n';
        std::cout << "Enter one of the listed values: ";
        std::cin >> mode_select;
        if (std::find(std::begin(valid_modes), std::end(valid_modes), mode_select) != std::end(valid_modes)) {
            break;
        } else {
            std::cout << "Invalid mode select, try again!" << '\n';
        }
    }

    switch (mode_select) {
        case 0: {
            //Singlethreaded.
            std::cout << '\n';
            std::cout << "Starting singlethreaded benchmark..." << '\n';
            //Log UTC time and print to std::cout.
            auto UTC_start_time = std::chrono::system_clock::now();
            std::cout << "\nStarted at: " << func::to_UTC(UTC_start_time) << '\n';
            prog_start_time = std::chrono::steady_clock::now();

            for (int k = 0; k < repeat_val; k++) {
                std::cout << "Iteration " << (k + 1) << " of " << repeat_val << " Runtime (ns): ";
                auto iteration_start_time = std::chrono::steady_clock::now();

                primes_in_range(lower_search_limit, upper_search_limit);

                auto iteration_stop_time = std::chrono::steady_clock::now();
                std::chrono::duration<uint64_t, std::nano> elapsed_single_iteration = iteration_stop_time - iteration_start_time; //how many nanoseconds have elapsed.
                iteration_length_arr[k] = elapsed_single_iteration.count(); //store elapsed_single_iteration nanoseconds in iteration_length_arr.
                std::cout << elapsed_single_iteration.count() << '\n';
            }

            avg_search_time = std::accumulate(std::begin(iteration_length_arr), std::end(iteration_length_arr), avg_search_time) / repeat_val;

            prog_stop_time = std::chrono::steady_clock::now();
            elapsed_prog_runtime = prog_stop_time - prog_start_time; //how many nanoseconds have elapsed.
            prog_runtime_nanoseconds = elapsed_prog_runtime.count();

            std::cout << "Prime singlethreaded benchmark is done!" << '\n';

            //Log UTC time and print to std::cout.
            auto UTC_stop_time = std::chrono::system_clock::now();
            std::cout << "\nStopped at: " << func::to_UTC(UTC_stop_time) << '\n';

            std::cout << "\n**** Results ****" << '\n';
            std::cout << "Search started at: " << func::to_UTC(UTC_start_time) << '\n';
            std::cout << "Search ended at: " << func::to_UTC(UTC_stop_time) << '\n';
            std::cout << "Program ran for total of (DD:HH:MM:SS.SSSSSSSSS): " << func::to_days_hours_minutes_seconds(prog_runtime_nanoseconds) << '\n';
            std::cout << "\n";
            std::cout << "Program ran for: " << prog_runtime_nanoseconds << " ns" << '\n';
            std::cout << "\n";
            std::cout << "Average time to find all primes between " << lower_search_limit << " and " << upper_search_limit << " was (DD:HH:MM:SS.SSSSSSSSS):" << '\n';
            std::cout << func::to_days_hours_minutes_seconds((uint64_t) avg_search_time) << '\n';
            std::cout << "\n";
            std::cout << "Average search time: " << (uint64_t) avg_search_time << " ns" << '\n';
            std::cout << "Number of primes found is: " << prime_count / repeat_val << '\n';

            break;
        }
        case 1: {
            //Multithreaded.
            std::cout << '\n';
            result = std::div(upper_search_limit, (long) thread_count);
            std::cout << "Numerator (also upper search limit): " << upper_search_limit << '\n';
            std::cout << "Denominator (also how many threads): " << thread_count << '\n';
            std::cout << "Quotient: " << result.quot << '\n';
            std::cout << "Remainder: " << result.rem << '\n';
            std::cout << "  ****  " << '\n';
    
            //Calculating start and end vales for the ranges.
            for (int i = 0; i < thread_count; i++) {
                if (i == 0) {
                    start_of_range.push_back(lower_search_limit);
                    end_of_range.push_back(result.quot);
                } else {
                    start_of_range.push_back(end_of_range[i - 1] + 1);
                    end_of_range.push_back((start_of_range[i] - 1) + result.quot);
                }
            }
    
            //Calculating start and end values for remainder range.
            if (result.rem != 0) {
                remainder_range_start = (upper_search_limit - result.rem) + 1;
                remainder_range_end = upper_search_limit;
            }

            std::cout << "Starting multithreaded prime benchmark..." << '\n';
            //Log UTC time and print to std::cout.
            auto UTC_start_time = std::chrono::system_clock::now();
            std::cout << "\nStarted at: " << func::to_UTC(UTC_start_time) << '\n';
            prog_start_time = std::chrono::steady_clock::now();

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

            prog_stop_time = std::chrono::steady_clock::now();
            elapsed_prog_runtime = prog_stop_time - prog_start_time; //how many nanoseconds have elapsed.
            prog_runtime_nanoseconds = elapsed_prog_runtime.count();

            std::cout << "Prime multithreaded benchmark is done!" << '\n';

            //Log UTC time and print to std::cout.
            auto UTC_stop_time = std::chrono::system_clock::now();
            std::cout << "\nStopped at: " << func::to_UTC(UTC_stop_time) << '\n';

            std::cout << "\n**** Results ****" << '\n';
            std::cout << "Search started at: " << func::to_UTC(UTC_start_time) << '\n';
            std::cout << "Search ended at: " << func::to_UTC(UTC_stop_time) << '\n';
            std::cout << "Program ran for total of (DD:HH:MM:SS.SSSSSSSSS): " << func::to_days_hours_minutes_seconds(prog_runtime_nanoseconds) << '\n';
            std::cout << "\n";
            std::cout << "Program ran for: " << prog_runtime_nanoseconds << " ns" << '\n';
            std::cout << "\n";
            std::cout << "Average time to find all primes between " << lower_search_limit << " and " << upper_search_limit << " was (DD:HH:MM:SS.SSSSSSSSS):" << '\n';
            std::cout << func::to_days_hours_minutes_seconds((uint64_t) avg_search_time) << '\n';
            std::cout << "\n";
            std::cout << "Average search time: " << (uint64_t) avg_search_time << " ns" << '\n';
            std::cout << "Number of primes found is: " << prime_count / repeat_val << '\n';

            break;
        }
        case 2:
            //Exit program.
            std::cout << "Exited program." << '\n';
            break;
        default:
            std::cout << "Defaulted to exiting program since no valid input was made." << '\n';
            std::exit(EXIT_FAILURE);
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
