#ifndef EMCACHE_UTIL_H
#define EMCACHE_UTIL_H

#include<stdlib.h>
#include<sys/time.h>
#include<stdint.h>


namespace emcache
{

    long long timeInMilliseconds(void);

    long timeInSeconds(void);

    typedef  uint64_t  TimeValue;
    typedef  int       ThreadId;

    //#define LOG_MESSAGE(msg)  std::cout <<
    void MilliSleep(TimeValue time_in_ms);

    void MicroSleep(TimeValue time_in_ms);


} //namespace emcache


#endif

