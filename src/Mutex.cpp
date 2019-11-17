#include "Mutex.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <errno.h>

using namespace emcache;
using namespace std;

Mutex::Mutex()
{
    Init();
}


Mutex::~Mutex()
{
    // TODO: check whether the mutex is in unlocked state.
    
    pthread_mutex_destroy(&m_mutex);
    
}



void Mutex::Lock()
{
    
    pthread_mutex_lock(&m_mutex);
}

void Mutex::Unlock()
{
    
    pthread_mutex_unlock(&m_mutex);
}


bool Mutex::TryLock()
{
    
    int res = pthread_mutex_trylock(&m_mutex);
    assert(res != EINVAL);
    return (res == 0);
    
}

pthread_mutex_t*  Mutex::getMutexPtr() {
    return &m_mutex;
}

void Mutex::Init()
{
    
    if (pthread_mutex_init(&m_mutex, NULL) != 0)
    {
        throw runtime_error("failed to initialize mutex");
    }
        
}


MutexLocker::MutexLocker(Mutex& m)
: m_mutex(m)
{
    m_mutex.Lock();
}

MutexLocker::~MutexLocker()
{
    m_mutex.Unlock();
}
