# Monitor and Conditional Variables

## Conditional Variable

Mutexes provide mutual exclusion in multithreaded programming and can be used to protect the critical section. However, threads might need to cooperate and wait for a condition to be satisfied before entering a critical section. To facilitate this, the Standard C++ Library introduced `std::condition_variable` in C++11.

## Wait Member Function

First, threads that intend to wait for a condition must acquire a mutex using `std::unique_lock`. As explained below, the lock must be able to unlock and relock the mutex during the wait, which is why `std::unique_lock` should be used as the mutex wrapper class.

The lock is then passed to the `std::condition_variable::wait` member function, and the wait member function atomically unlocks the lock and blocks the thread. A blocked thread is unblocked if notified by a thread or is woken up spuriously. Additionally, a predicate (condition) can be supplied to the wait member function to prevent spurious wake-up.

Finally, the unblocked thread reacquires the mutex before proceeding to the critical section.

## notify_one Member Function

A thread can acquire the mutex using a mutex wrapper class (e.g., `std::scoped_lock`), and it then modifies the shared data while holding the mutex.

Finally, it notifies one thread by calling `std::condition_variable::notify_one`, or all threads by calling `notify_all`.

## Monitor

A monitor is a class or module that encapsulates a set of programmer-defined member functions and variables that are modified by these functions, along with the mutex and condition variables.

The mutex in the monitor ensures that only one thread or process is active inside its public member functions, so the programmer does not need to synchronize explicitly.

The condition variable blocks a thread inside a member function when it must wait for a condition to be fulfilled.

The attached sample code demonstrates the structure of a monitor.
