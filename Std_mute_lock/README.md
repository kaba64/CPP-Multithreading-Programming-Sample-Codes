# Mutual Exclusion (Mutex) and Mutex Wrapper Classes

## Mutex

Mutex is an object that provides mutual exclusion to synchronize access to shared data or resources. The std::mutex is the simplest and fastest mutex introduced in C++11, and it is a wrapper around the mutex variable provided by the underlying system.

Mutex class has the lock() and unlock() member functions to gain exclusive access to the critical section.

The mutex object is not copyable and movable.

The std::recursive_mutex and std::timed_mutex are variants of the std::mutex with additional functionality and some overhead.

## std::lock_guard

The standard C++ library provides different classes implementing RAII for locking and unlocking mutex, and these classes help prevent forgetting to unlock the mutex when it goes out of scope and in the presence of throwing an exception.

The std::lock_guard is the simplest and fastest RAII wrapper introduced in C++11, and it acquires (locks) the mutex in the constructor or adopts the already acquired mutex by the thread by supplying the std::adopt_lock argument to the std::lock_guard. Indeed, it is a handle to a lockable object.

The std::lock_guard is not copyable.

On many systems, the std::lock_guard object is 8 bytes in size with one private member mutex_type&.

```cpp
private: /* From Linux implementation */
      mutex_type&  _M_device;

## std::unique_lock

The std::unique_lock class provides an RAII mechanism and more operations on the mutex, which makes it a general-purpose mutex ownership mechanism.

The std::unique_lock is movable, but not copyable. As a result, it is suitable when we want to pass the ownership of the lock outside of the scope created.

It provides different constructors, which enables it to construct an object without owning a mutex or locking a mutex in the constructor by providing std::defere_lock and similar arguments. The destructor of the class unlocks the mutex if it holds one. The mutex can be locked and unlocked by the lock() and unlock() member functions.

These flexibilities come with the price of more memory usage, 16 bytes on my system, and a slight decline in performance. It uses a boolean flag in addition to the mutex_type&

```cpp
private: /* From Linux implementation */
      mutex_type*       _M_device;      
      bool              _M_owns;

## std::lock

It is possible to get deadlock when there is a need to acquire more than one shared mutexes by different threads. The standard C++ library introduced the std::lock class in C++11 with a variadic template to lock different lockable objects with a deadlock avoidance algorithm, and the objects are locked in an unspecified order by the call to the lock and try_lock member function.

The std::lock is usually used with std::unique_lock or std::lock_guard to unlock the mutexes automatically.

## std::scoped_lock

The std::scoped_lock is introduced in C++17. It is a wrapper around the mutex for providing RAII, like the std::lock_guard class, but with a variadic template allowing it to acquire more than one mutex with a deadlock avoidance algorithm like the std::lock class.

This class is more efficient and concise to use when there is a need to acquire more than one lock by different threads simultaneously.

The std::scoped_lock class is not copyable.