# Executing Tasks Asynchronously Using std::async:

We can divide the computation into multiple tasks and run them asynchronously or potentially concurrently on different hardware threads. The C++ Standard Library offers two mechanisms to achieve this goal, each with its merits. 

We can launch new threads using std::thread to run the tasks concurrently, but we are responsible for synchronizing and managing the threads. Alternatively, we can use the task-based concurrency facilities in C++, e.g. std::async, to run the new tasks asynchronously.

## Using std::thread:

The std::thread class allows the immediate execution of the function after constructing an object of its type. If a function launched on a std::thread has a return value, it will be ignored.

The std::terminate is called if a thread throws an exception during the execution. Moreover, the constructor of std::thread can throw an exception upon failure to start.

## Using std::async:

A std::future object is returned after launching the f(args) function asynchronously using the std::async. The returned value of the function can be obtained using the std::future::get member function.

The task can be run on the current thread, on a new thread, or using a thread from the thread pool depending on the launch policy.

- The launch policy std::launch::async directs the launcher to execute the task on a different thread.

- The launch policy std::launch::deferred directs the launcher to run the task on the thread that launched the task, after a call to std::future::get or std::future::wait. The current thread will be blocked until the return of std::future::get.

- The default policy is (std::launch::async | std::launch::deferred), and the task of deciding which to choose is delegated to the implementation.


## References:

[1] C++ Programming Language, Fourth Edition
[2] https://en.cppreference.com/w/cpp/thread/async
[3] https://en.cppreference.com/w/cpp/thread/future