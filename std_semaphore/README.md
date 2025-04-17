# Semaphores, `std::counting_semaphore`, and `std::binary_semaphore` on Linux

## Semaphores

Proposed by Edsger Dijkstra, semaphores are software abstractions that support two atomic operations: `acquire` and `release`, typically on an integer or struct. A semaphore has a counter (`_M_sem`), which is initialized to the number of resources. The key atomic operations supported by semaphores are:

1. **Acquire**: `_M_sem` is atomically loaded by a thread or process. If `_M_sem` is zero, it is blocked and placed on the waiting list. Otherwise, the value of `_M_sem` is atomically decremented by one (`_M_sem - 1`).

2. **Release**: `_M_sem` is atomically loaded and incremented. If the old value of `_M_sem` was zero, then a thread or process is removed from the waiting list and allowed to continue execution.

A **binary semaphore** can have values of zero and one. It can be used to implement mutual exclusion.

A **counting semaphore** can be used to control access to resources consisting of a finite number of instances.

---

## `std::counting_semaphore`

`std::counting_semaphore` is a template class introduced in C++20 whose internal counter is initialized via its constructor. It provides the `acquire` and `release` member functions with the same behavior described above.

The `std::counting_semaphore` class is a wrapper around two other classes depending on the version of C++ available. The following snippet is from libstdc++:

```
#if defined __cpp_lib_atomic_wait &&  _GLIBCXX_USE_POSIX_SEMAPHORE
  using __semaphore_impl = __atomic_semaphore;
#elif _GLIBCXX_HAVE_POSIX_SEMAPHORE
  using __semaphore_impl = __platform_semaphore;
#endif
```

If the compiler and standard library support std::atomic_wait() (a C++20 feature) and _GLIBCXX_USE_POSIX_SEMAPHORE is not set, then it uses an implementation based on atomic variables and std::atomic::wait().

If libstdc++ has POSIX semaphores available (e.g., sem_post, sem_wait from <semaphore.h>) and _GLIBCXX_USE_POSIX_SEMAPHORE is set, it falls back to using the platform’s native implementation, such as glibc’s sem_t, sem_init, sem_wait, and sem_post.
std::binary_semaphore

std::binary_semaphore:

std::binary_semaphore is simply a specialization of the counting semaphore: std::counting_semaphore<1>.

It can be used to implement mutual exclusion. A thread can acquire the binary semaphore and access the critical section if the counter is 1; otherwise, if it is 0, the thread will be blocked until another thread executes a release on the same binary semaphore.

The main difference between std::mutex and std::binary_semaphore is that the thread that locked the mutex must also unlock it to allow another thread to gain the lock. In contrast, any thread can release the binary semaphore, enabling another thread to acquire it.
