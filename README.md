# ezTool
The basic API can be used in kernel space and user space.
Because the lock and schedule APIs are different between the two spaces, I only implement the lowest level feature.
For example, lock. In user space, it is pthread_mutex_lock. In kernel space, it is mutex_lock.