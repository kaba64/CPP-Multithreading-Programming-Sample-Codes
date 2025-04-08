# The Linux Fast User-Space Mutex (Futex)

In multithreading and multiprocess programming, there is a need for synchronization if threads/processes need to manipulate a shared physical address or resource. There are two general ways to deal with this issue. 

The first approach does not involve the operating system (OS). Instead, a lock can be implemented using atomic operations provided by the underlying system, such as "compare_and_swap". This approach is fast, and the Spinlock is a good example. It is suitable when the waiting time to acquire the lock is short, usually less than two context switches.

In the second approach, threads or processes are blocked and placed in a waiting queue when the lock is unavailable. This allows other threads or processes to utilize the CPU core. They remain blocked until the lock becomes free. This approach needs the involvement of the OS, so it is usually expensive compared to the first approach.

The futex combines the best of the two approaches. It is an efficient, kernel-assisted locking primitive in Linux for user-space applications. The state of the lock is stored in a user-space variable ( a 32-bit integer ), and the lock is acquired by using atomic operation in the user-space in the uncontended situation.  However, in cases of contention, the kernel is invoked via a system call (SYS_futex) to block the process or thread, placing it in a waiting queue. The thread or process that owns the lock can then use the wake operation via another system call to awaken a thread or process from the waiting queue.

Futexes are a very low-level feature of the kernel and are used to implement synchronization facilities, e.g. Pthread mutexes and semaphores, by the standard libraries.

## Reference

[1] https://manpages.ubuntu.com/manpages/bionic/man2/futex.2.html
