# Synchronizing Groups of Threads Using Barriers:

The class template 'std::barrier' was introduced in C++20. It is a reusable synchronization component that blocks a group of threads until they all reach the barrier.

Each thread in the synchronization group can call the 'std::barrier::arrive_and_wait' member function to decrement an internal phase counter, initialized from the expected thread count provided during construction. When the value of the expected count reaches zero, the barrier's CompletionFunction is called; this point is known as the phase completion step. There is a strong happens-before relationship between the return from the CompletionFunction and the threads unblocked by the std::barrier::arrive_and_wait function. As a result, this guarantees visibility of writes in the completion function to the unblocked threads, helping to avoid data races for correctly synchronized variables.

Finally, the expected count is reset to the value given at construction. If other member functions are called, the value of the expected count may be decreased.

The 'std::barrier' object can be used in the next iteration.

Reference:

[1] https://en.cppreference.com/w/cpp/thread/barrier#Data_members
