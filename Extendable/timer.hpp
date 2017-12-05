#ifndef TIMER_HPP
#define TIMER_HPP

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>

class Timer
{
public:
  Timer() : total(0), average(0) {}

  double total;
  std::vector<double> times;
  double average;
  std::chrono::time_point<std::chrono::system_clock> _start, _end;

  // time a function and add time to list of times
  template <typename F>
  auto time(F f)
  {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();

    auto result = std::chrono::duration<double, std::milli>(end - start).count();

    times.push_back(result); // save()

    // std::cout << result << " Milli" << std::endl;

    return result;
  }

  // save current total
  void save()
  {
    times.push_back(total);
    total = 0;
  }

  // return current total time
  double getTime() { return total; }

  // calculates the standard deviation
  double getStdDev()
  {
    double avg = getAverage();
    double dev = 0;
    for (auto&& e : times) dev += pow((e - avg), 2);
    return sqrt(dev / times.size());
  }

  // calculates average
  double getAverage()
  {
    double sum = std::accumulate(times.begin(), times.end(), 0.0);
    return sum / times.size();
  }

  // resets all values
  void reset()
  {
    total = 0;
    average = 0;
    times.clear();
  }
};

/*
//start timer
void start()
{
        _start = std::chrono::high_resolution_clock::now();
}

//stop timer
void end()
{
        _end = std::chrono::high_resolution_clock::now();
        add();
}

//add current time to total
void add()
{
        total += calcTime();
}

//return time segment
double calcTime()
{
        return std::chrono::duration <double, std::milli>(_end -
_start).count();
}
*/

#endif
