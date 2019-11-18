#ifndef EMCACHE_MUTEX_H_
#define EMCACHE_MUTEX_H_

#include <pthread.h>
#include <boost/noncopyable.hpp>
#include <cassert>

namespace emcache
{

    class Mutex : private boost::noncopyable
    {

    public:
        Mutex();
        ~Mutex();

        // These two functions can only called by MutexLocker
        void Lock();
        void Unlock();
        bool TryLock();
        void Init();
        pthread_mutex_t *getMutexPtr();

    private:
        pthread_mutex_t m_mutex;
    };

    class MutexLocker : private boost::noncopyable
    {
    public:
        explicit MutexLocker(Mutex &m);
        ~MutexLocker();

    private:
        Mutex &m_mutex;
    };


}  // namespace emcache

#endif
