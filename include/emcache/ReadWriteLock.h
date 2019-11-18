#ifndef EMCACHE_READ_WRITE_LOCK
#define EMCACHE_READ_WRITE_LOCK

#include "Mutex.h"
#include "ConditionVariable.h"

namespace emcache
{
    class ReadWriteLock
    {
    public:
        ReadWriteLock();
        ~ReadWriteLock();

        void ReadLock();
        void ReadUnlock();
        void WriteLock();
        void WriteUnlock();
    private:
        Mutex m_mutex;
        ConditionVariable m_cond;
        int m_readCount;// read thread num
        int m_writeCount;//write-wait thread    
    };

    class ReadLockGuard
    {

    public:
        ReadLockGuard(ReadWriteLock &readWirteLock);
        ~ReadLockGuard();

    private:
        ReadWriteLock &m_readWriteLock;
    };


    class WriteLockGuard
    {
    public:
        WriteLockGuard(ReadWriteLock  &readWirteLock);
        ~WriteLockGuard();

    private:
        ReadWriteLock  &m_readWriteLock;
    };

} //namespace emcache

#endif