# Synchronized Stream Writes Using std::mutex and std::osyncstream in Multi-threaded C++:

A race condition can occur in multi-threaded programming when the outcome of an operation depends on the relative order of execution of that operation across different threads.

While the standard library guarantees that the std::cout variable is protected from corruption, a potential race condition might occur when multiple threads write to the std::cout without mutual exclusion, and the threads' output may interleave.

The C++ Standard Library provides various facilities to prevent this interleaving.

## Using mutex and locks:

We can use the mutual exclusion and locking facilities introduced in C++11 to prevent thread output from interleaving:

```c
std::mutex = m_io;

...

{
	std::lock_guard<std::mutex> lk(m_io);
	std::cout<<message<<'\n';
}

```

Each thread acquires the lock before writing to std::cout, ensuring exclusive access to the output stream.

## The std::basic_syncbuf class:

The std::basic_syncbuf class is introduced in C++20, and it is a wrapper around the std::basic_streambuf.

It has an internal buffer in addition to other members. 

The output is accumulated into std::basic_syncbuf's internal buffer and transferred atomically to its wrapper upon its destruction or when requested by the std::basic_syncbuf::emit() member function.

## Using std::basic_osyncstream:

The std::basic_osyncstream class wraps std::basic_syncbuf and enables synchronized output to streams like std::cout in multi-threaded programs.

This prevents the output from different threads from becoming intermixed.
