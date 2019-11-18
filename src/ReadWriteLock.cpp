#include "ReadWriteLock.h"

using namespace emcache;




ReadWriteLock::ReadWriteLock()
    : m_mutex(),
      m_cond(m_mutex),
      m_readCount(0),
      m_writeCount(0)
{}


ReadWriteLock::~ReadWriteLock()
{}



void ReadWriteLock::ReadLock()
{
    m_cond.Lock();
    ++m_readCount;
    while(m_writeCount > 0)
    {
        m_cond.Wait();
    }
    m_cond.Unlock();
}


void ReadWriteLock::ReadUnlock()
{
    m_cond.Lock();
    --m_readCount;
    if (0 == m_readCount)
    {
        m_cond.Notify();
    }
    m_cond.Unlock();
}


void ReadWriteLock::WriteLock()
{
    m_cond.Lock();
    ++m_writeCount;
    while(m_writeCount + m_readCount >= 2)
    {
        m_cond.Wait();
    }
    m_cond.Unlock();
}


void ReadWriteLock::WriteUnlock()
{
    m_cond.Lock();
    --m_writeCount;
    if (m_writeCount == 0)
    {
        m_cond.Notify();
    }
    m_cond.Unlock();
}


ReadLockGuard::ReadLockGuard(ReadWriteLock  &readWriteLock)
    : m_readWriteLock(readWriteLock)
{
    m_readWriteLock.ReadLock();
}


ReadLockGuard::~ReadLockGuard()
{
    m_readWriteLock.ReadUnlock();
}

WriteLockGuard::WriteLockGuard(ReadWriteLock  &readWriteLock)
    : m_readWriteLock(readWriteLock)
{
    m_readWriteLock.WriteLock();
}


WriteLockGuard::~WriteLockGuard()
{
    m_readWriteLock.WriteUnlock();
}
