# Timing Facilities Provided by the C++ Standard Library:

A program may need to compute the duration of time spent during a specific computation or determine the time in a particular time zone. The C++ Standard Library provides facilities in the <chrono> header file to obtain this information.

## Duration:

The class template 'std::chrono::duration' represents a time interval between two time points. For example

```c
std::chrono::duration<double,std::ratio<1,10>> 
```
Represents a duration with a period of 10 clock ticks per second stored in a count of ticks with type double. 

## Time points:

The class template 'std::chrono::time_point' represents a point in time relative to the epoch of a clock. The class needs a clock for its argument, and it supplies the reference point for the epoch. For example
```c
std::chrono::time_point<std::chrono::system_clock>
```
Uses 'system_clock' for the epoch reference point.

## Clocks:

A clock consists of a starting point and a tick rate. The C++ Standard Library provides several clocks. Three commonly used ones are described below.

All clocks have the member function 'now()' to get the current point in time.

## The system_clock class:

The class 'std::chrono::system_clock' represents the wall clock time obtained from the system-wide real-time wall clock. Its ticks are not uniform because the clock can be adjusted.

It is the only standard C++ clock that can directly interoperate with C-style time, such as the type 'std::time_t'.

## The steady_clock class:

The class 'std::chrono::steady_clock' ensures that the time between ticks is constant, making it better for measuring time intervals.

## The high_resolution_clock class:

The class 'std::chrono::high_resolution_clock' is a clock with the shortest time increment in the system. It may be an alias of 'steady_clock' and 'system_clock'.

## The clock() function:

std::clock() approximates how much processor time has been used by a process since the CRT initialization. 

std::clock may advance faster than the wall clock if the process has more than one thread and they run on different cores simultaneously.

## Reference:

[1] https://en.cppreference.com/w/cpp/chrono
