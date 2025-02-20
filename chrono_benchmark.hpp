/**
* @file chrono_benchmark.hpp
* @brief chrono benchmark class utilizing RAII
* @version 1.1
* @date 2025-01-19
*/

#ifndef CHRONO_BENCHMARK_HPP
#define CHRONO_BENCHMARK_HPP

#include <chrono>
#include <iostream>

class ChronoTimer
{
  public:
    ChronoTimer()
    {
      timer_starting_point = std::chrono::high_resolution_clock::now();
    }

    ~ChronoTimer()
    {
      Stop();
    }

  // RAII
  void Stop()
  {
    // immediately get the current time for the end time
    std::chrono::_V2::system_clock::time_point timer_ending_point{std::chrono::high_resolution_clock::now()};

    // begin conversions                                                      std::int64_t
    std::int64_t start_microseconds{std::chrono::time_point_cast<std::chrono::microseconds>(timer_starting_point).time_since_epoch().count()};
    std::int64_t end_microseconds{std::chrono::time_point_cast<std::chrono::microseconds>(timer_ending_point).time_since_epoch().count()};

    std::int64_t total_duration_microseconds{end_microseconds - start_microseconds};

    // convert micro to milli                       cast
    double total_duration_milliseconds{static_cast<double>(total_duration_microseconds) * 0.001};

    std::cout << total_duration_milliseconds << "millis" << std::endl;
  }

  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> timer_starting_point;

};

#endif // CHRONO_BENCHMARK_HPP