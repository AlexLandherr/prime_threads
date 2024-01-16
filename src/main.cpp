#include "include/functions.h"
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
#include <algorithm>
#include <ctime>
#include <fstream>
#include <stdexcept>
#include <filesystem>

void primes_in_range(uint64_t lower_limit, uint64_t upper_limit);

std::atomic<unsigned int> prime_count = 0;

int main() {
    using namespace std::chrono_literals;
    auto thread_count = std::thread::hardware_concurrency();
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

    //Checking if 'logs' directory exists; if not then it's created.
    std::filesystem::path directory_path{"logs"};
    std::cout << "Checking '" << directory_path.string() << "' directory status..." << '\n';
    if (std::filesystem::exists(directory_path)) {
        std::cout << "'" << directory_path.string() << "' exists." << '\n';
    } else {
        std::cout  << "'" << directory_path.string() << "' directory does not exist or has changed name!" << '\n';
        std::cout <<  "Creating '" << directory_path.string() << "' directory." << '\n';
        std::filesystem::create_directory(directory_path);
    }
    std::cout << "    ****    " << '\n';

    auto UTC_prog_start_time = std::chrono::system_clock::now();
    std::string log_file_name_str = "";
    try {
        log_file_name_str = func::replace_char(' ', '_', func::to_UTC(UTC_prog_start_time));
        log_file_name_str = func::replace_char(':', '-', log_file_name_str);
    } catch (const std::invalid_argument& ex) {
        std::cerr << ex.what() << '\n';
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << '\n';
    }

    constexpr int repeat_val = 10;
    std::array<uint64_t, repeat_val> iteration_length_arr;
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

    std::chrono::_V2::steady_clock::time_point search_start_time;
    std::chrono::_V2::steady_clock::time_point search_stop_time;
    uint64_t search_runtime_nanoseconds = 0;
    std::chrono::duration<uint64_t, std::nano> elapsed_search_runtime;

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
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "\n\nThat's an invalid input! Please try again." << '\n';
        } else if (std::find(std::begin(valid_modes), std::end(valid_modes), mode_select) != std::end(valid_modes)) {
            break;
        } else {
            std::cerr << "\nInvalid mode select, try again!" << '\n';
        }
    }

    switch (mode_select) {
        case 0: {
            //Singlethreaded.
            std::cout << "\nStarting singlethreaded benchmark..." << '\n';
            
            //Log UTC time and print to std::cout.
            auto UTC_search_start_time = std::chrono::system_clock::now();
            std::cout << "\nStarted at: " << func::to_UTC(UTC_search_start_time) << '\n';
            search_start_time = std::chrono::steady_clock::now();

            for (int k = 0; k < repeat_val; k++) {
                std::cout << "Iteration " << (k + 1) << " of " << repeat_val << " Runtime (ns): ";
                auto iteration_start_time = std::chrono::steady_clock::now();

                try {
                    primes_in_range(lower_search_limit, upper_search_limit);
                } catch (const std::invalid_argument& ex) {
                    std::cerr << ex.what() << '\n';
                } catch (const std::exception& ex) {
                    std::cerr << ex.what() << '\n';
                }

                auto iteration_stop_time = std::chrono::steady_clock::now();
                std::chrono::duration<uint64_t, std::nano> elapsed_single_iteration = iteration_stop_time - iteration_start_time; //how many nanoseconds have elapsed.
                iteration_length_arr[k] = elapsed_single_iteration.count(); //store elapsed_single_iteration nanoseconds in iteration_length_arr.
                std::cout << elapsed_single_iteration.count() << '\n';
            }

            avg_search_time = std::accumulate(std::begin(iteration_length_arr), std::end(iteration_length_arr), avg_search_time) / repeat_val;

            search_stop_time = std::chrono::steady_clock::now();
            elapsed_search_runtime = search_stop_time - search_start_time; //how many nanoseconds have elapsed.
            search_runtime_nanoseconds = elapsed_search_runtime.count();

            std::cout << "Prime singlethreaded benchmark is done!" << '\n';

            //Log UTC time and print to std::cout.
            auto UTC_search_stop_time = std::chrono::system_clock::now();
            std::cout << "\nStopped at: " << func::to_UTC(UTC_search_stop_time) << '\n';

            std::cout << "\n**** Results ****" << '\n';
            std::cout << "Program mode is: Singlethreaded" << '\n';
            std::cout << "Search started at: " << func::to_UTC(UTC_search_start_time) << '\n';
            std::cout << "Search ended at: " << func::to_UTC(UTC_search_stop_time) << '\n';
            try {
                std::cout << "Search ran for total of (DD:HH:MM:SS.SSSSSSSSS): " << func::to_days_hours_minutes_seconds(search_runtime_nanoseconds) << '\n';
            } catch (const std::invalid_argument& ex) {
                std::cerr << ex.what() << '\n';
            } catch (const std::exception& ex) {
                std::cerr << ex.what() << '\n';
            }
            std::cout << "\n";
            std::cout << "Search ran for: " << search_runtime_nanoseconds << " ns" << '\n';
            std::cout << "\n";
            std::cout << "Average time to find all primes between " << lower_search_limit << " and " << upper_search_limit << " was (DD:HH:MM:SS.SSSSSSSSS):" << '\n';
            try {
                std::cout << func::to_days_hours_minutes_seconds(static_cast<uint64_t>(avg_search_time)) << '\n';
            } catch (const std::invalid_argument& ex) {
                std::cerr << ex.what() << '\n';
            } catch (const std::exception& ex) {
                std::cerr << ex.what() << '\n';
            }
            std::cout << "\n";
            std::cout << "Average search time: " << static_cast<uint64_t>(avg_search_time) << " ns" << '\n';
            std::cout << "Number of primes found is: " << prime_count / repeat_val << '\n';

            //Writing results to unique log file with time stamp as file name.
            std::fstream log_fs{"logs/Prime_Threads_Log_File_" + log_file_name_str + ".txt", std::ios::out};
            log_fs << "**** Results ****" << '\n';
            log_fs << "Program mode is: Singlethreaded" << '\n';
            log_fs << "Search started at: " << func::to_UTC(UTC_search_start_time) << '\n';
            log_fs << "Search ended at: " << func::to_UTC(UTC_search_stop_time) << '\n';
            try {
                log_fs << "Search ran for total of (DD:HH:MM:SS.SSSSSSSSS): " << func::to_days_hours_minutes_seconds(search_runtime_nanoseconds) << '\n';
            } catch (const std::invalid_argument& ex) {
                std::cerr << ex.what() << '\n';
            } catch (const std::exception& ex) {
                std::cerr << ex.what() << '\n';
            }
            log_fs << '\n';
            log_fs << "Search ran for: " << std::to_string(search_runtime_nanoseconds) << " ns" << '\n';
            log_fs << '\n';
            log_fs << "Average time to find all primes between " << lower_search_limit << " and " << upper_search_limit << " was (DD:HH:MM:SS.SSSSSSSSS):" << '\n';
            try {
                log_fs << func::to_days_hours_minutes_seconds(static_cast<uint64_t>(avg_search_time)) << '\n';
            } catch (const std::invalid_argument& ex) {
                std::cerr << ex.what() << '\n';
            } catch (const std::exception& ex) {
                std::cerr << ex.what() << '\n';
            }
            log_fs << '\n';
            log_fs << "Average search time: " << std::to_string(static_cast<uint64_t>(avg_search_time)) << " ns" << '\n';
            log_fs << "Number of primes found is: " << std::to_string(prime_count / repeat_val) << '\n';
            log_fs << "\n**** Runtime for each iteration ****" << '\n';
            for (int i = 0; i < repeat_val; i++) {
                log_fs << "Iteration " << (i + 1) << " of " << repeat_val << " Runtime (ns): " << static_cast<uint64_t>(iteration_length_arr[i]) << '\n';
            }
            log_fs << '\n';

            break;
        }
        case 1: {
            //Multithreaded.
            result = std::div(upper_search_limit, static_cast<long>(thread_count));
            std::cout << "\nNumerator (also upper search limit): " << upper_search_limit << '\n';
            std::cout << "Denominator (also how many threads): " << thread_count << '\n';
            std::cout << "Quotient: " << result.quot << '\n';
            std::cout << "Remainder: " << result.rem << '\n';
            std::cout << "  ****  " << '\n';
    
            //Calculating start and end vales for the ranges.
            for (unsigned int i = 0; i < thread_count; i++) {
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
            auto UTC_search_start_time = std::chrono::system_clock::now();
            std::cout << "\nStarted at: " << func::to_UTC(UTC_search_start_time) << '\n';
            search_start_time = std::chrono::steady_clock::now();

            for (int k = 0; k < repeat_val; k++) {
                std::cout << "Iteration " << (k + 1) << " of " << repeat_val << " Runtime (ns): ";
                //Create vector to hold main thread objects.
                std::vector<std::thread> main_threads;

                auto iteration_start_time = std::chrono::steady_clock::now();
                //Create and start main threads.
                for (unsigned int i = 0; i < thread_count; i++) {
                    try {
                        main_threads.push_back(std::thread(primes_in_range, start_of_range[i], end_of_range[i]));
                    } catch (const std::invalid_argument& ex) {
                        std::cerr << ex.what() << '\n';
                    } catch (const std::exception& ex) {
                        std::cerr << ex.what() << '\n';
                    }
                }

                //Join main threads.
                for (auto &th : main_threads) {
                    th.join();
                }

                //Create remainder thread (if needed).
                if (result.rem != 0) {
                    try {
                        std::thread remainder_thread = std::thread(primes_in_range, remainder_range_start, remainder_range_end);
                        
                        remainder_thread.join();
                    } catch (const std::invalid_argument& ex) {
                        std::cerr << ex.what() << '\n';
                    } catch (const std::exception& ex) {
                        std::cerr << ex.what() << '\n';
                    }
                }

                auto iteration_stop_time = std::chrono::steady_clock::now();
                std::chrono::duration<uint64_t, std::nano> elapsed_single_iteration = iteration_stop_time - iteration_start_time; //how many nanoseconds have elapsed.
                iteration_length_arr[k] = elapsed_single_iteration.count(); //store elapsed_single_iteration nanoseconds in iteration_length_arr.
                std::cout << elapsed_single_iteration.count() << '\n';
            }

            avg_search_time = std::accumulate(std::begin(iteration_length_arr), std::end(iteration_length_arr), avg_search_time) / repeat_val;

            search_stop_time = std::chrono::steady_clock::now();
            elapsed_search_runtime = search_stop_time - search_start_time; //how many nanoseconds have elapsed.
            search_runtime_nanoseconds = elapsed_search_runtime.count();

            std::cout << "Prime multithreaded benchmark is done!" << '\n';

            //Log UTC time and print to std::cout.
            auto UTC_search_stop_time = std::chrono::system_clock::now();
            std::cout << "\nStopped at: " << func::to_UTC(UTC_search_stop_time) << '\n';

            std::cout << "\n**** Results ****" << '\n';
            std::cout << "Program mode is: Multithreaded" << '\n';
            std::cout << "Thread count: " << thread_count << '\n';
            std::cout << "Search started at: " << func::to_UTC(UTC_search_start_time) << '\n';
            std::cout << "Search ended at: " << func::to_UTC(UTC_search_stop_time) << '\n';
            try {
                std::cout << "Search ran for total of (DD:HH:MM:SS.SSSSSSSSS): " << func::to_days_hours_minutes_seconds(search_runtime_nanoseconds) << '\n';
            } catch (const std::invalid_argument& ex) {
                std::cerr << ex.what() << '\n';
            } catch (const std::exception& ex) {
                std::cout << ex.what() << '\n';
            }
            std::cout << "\n";
            std::cout << "Search ran for: " << search_runtime_nanoseconds << " ns" << '\n';
            std::cout << "\n";
            std::cout << "Average time to find all primes between " << lower_search_limit << " and " << upper_search_limit << " was (DD:HH:MM:SS.SSSSSSSSS):" << '\n';
            try {
                std::cout << func::to_days_hours_minutes_seconds(static_cast<uint64_t>(avg_search_time)) << '\n';
            } catch (const std::invalid_argument& ex) {
                std::cerr << ex.what() << '\n';
            } catch (const std::exception& ex) {
                std::cerr << ex.what() << '\n';
            }
            std::cout << "\n";
            std::cout << "Average search time: " << static_cast<uint64_t>(avg_search_time) << " ns" << '\n';
            std::cout << "Number of primes found is: " << prime_count / repeat_val << '\n';

            //Writing results to unique log file with time stamp as file name.
            std::fstream log_fs{"logs/Prime_Threads_Log_File_" + log_file_name_str + ".txt", std::ios::out};
            log_fs << "**** Results ****" << '\n';
            log_fs << "Program mode is: Multithreaded" << '\n';
            log_fs << "Thread count: " << thread_count << '\n';
            log_fs << "Search started at: " << func::to_UTC(UTC_search_start_time) << '\n';
            log_fs << "Search ended at: " << func::to_UTC(UTC_search_stop_time) << '\n';
            try {
                log_fs << "Search ran for total of (DD:HH:MM:SS.SSSSSSSSS): " << func::to_days_hours_minutes_seconds(search_runtime_nanoseconds) << '\n';
            } catch (const std::invalid_argument& ex) {
                std::cerr << ex.what() << '\n';
            } catch (const std::exception& ex) {
                std::cerr << ex.what() << '\n';
            }
            log_fs << '\n';
            log_fs << "Search ran for: " << std::to_string(search_runtime_nanoseconds) << " ns" << '\n';
            log_fs << '\n';
            log_fs << "Average time to find all primes between " << lower_search_limit << " and " << upper_search_limit << " was (DD:HH:MM:SS.SSSSSSSSS):" << '\n';
            try {
                log_fs << func::to_days_hours_minutes_seconds(static_cast<uint64_t>(avg_search_time)) << '\n';
            } catch (const std::invalid_argument& ex) {
                std::cerr << ex.what() << '\n';
            } catch (const std::exception& ex) {
                std::cerr << ex.what() << '\n';
            }
            log_fs << '\n';
            log_fs << "Average search time: " << std::to_string(static_cast<uint64_t>(avg_search_time)) << " ns" << '\n';
            log_fs << "Number of primes found is: " << std::to_string(prime_count / repeat_val) << '\n';
            log_fs << "\n**** Runtime for each iteration ****" << '\n';
            for (int i = 0; i < repeat_val; i++) {
                log_fs << "Iteration " << (i + 1) << " of " << repeat_val << " Runtime (ns): " << static_cast<uint64_t>(iteration_length_arr[i]) << '\n';
            }
            log_fs << '\n';

            break;
        }
        case 2: {
            //Exit program.
            std::cout << "Exited program." << '\n';
            break;
        }
        default: {
            std::cout << "Defaulted to exiting program since no valid input was made." << '\n';
            std::exit(EXIT_FAILURE);
        }
        }

        auto UTC_prog_stop_time = std::chrono::system_clock::now();

        //Write start and end UTC times for complete program run.
        if (mode_select != 2) {
            try {
                std::fstream log_fs{"logs/Prime_Threads_Log_File_" + log_file_name_str + ".txt", std::ios::app};
                log_fs << "Program started at: " << func::to_UTC(UTC_prog_start_time) << '\n';
                log_fs << "Program ended at: " << func::to_UTC(UTC_prog_stop_time) << '\n';
                std::chrono::duration<uint64_t, std::nano> prog_runtime = UTC_prog_stop_time - UTC_prog_start_time;
                log_fs << "Program ran for a total of (DD:HH:MM:SS.SSSSSSSSS): " << func::to_days_hours_minutes_seconds(prog_runtime.count()) << '\n';
            } catch (const std::invalid_argument& ex) {
                std::cerr << ex.what() << '\n';
            } catch (const std::exception& ex) {
                std::cerr << ex.what() << '\n';
            }
        }
    
    return 0;
}

void primes_in_range(uint64_t lower_limit, uint64_t upper_limit) {
    if (lower_limit > std::numeric_limits<uint64_t>::max() || lower_limit < std::numeric_limits<uint64_t>::min()) {
        throw std::invalid_argument("'lower_limit' argument was out of range for 'uint64_t' type!");
    } else if (upper_limit > std::numeric_limits<uint64_t>::max() || upper_limit < std::numeric_limits<uint64_t>::min()) {
        throw std::invalid_argument("'upper_limit' argument was out of range for 'uint64_t' type!");
    }
    unsigned int count = 0;
    for (uint64_t i = lower_limit; i < upper_limit + 1; i++) {
        try {
            if (func::prime::is_prime(i)) {
                count++;
            }
        } catch (std::invalid_argument const& ex) {
            std::cerr << ex.what() << '\n';
        }
    }

    prime_count += count;
}
