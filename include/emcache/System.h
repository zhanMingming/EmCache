#ifndef EMCACHE_SYSTEM_H
#define EMCACHE_SYSTEM_H

namespace emcache
{


    const double  Mem_Used_Rate = 0.8;

#if defined(__GNUC__)
#define TPOOL_LIKELY(x)   (__builtin_expect((x), 1))
#define TPOOL_UNLIKELY(x) (__builtin_expect((x), 0))
#else
#define TPOOL_LIKELY(x) (x)
#define TPOOL_UNLIKELY(x) (x)
#endif


    extern __thread int t_cachedTid;
    extern __thread char t_tidString[32];
    extern __thread int t_tidStringLength;
    extern __thread const char *t_threadName;
    void CacheTid();

    inline int Tid()
    {
        if (TPOOL_UNLIKELY(t_cachedTid == 0))
        {
            CacheTid();
        }
        return t_cachedTid;
    }

    inline const char *TidString()
    {
        return t_tidString;
    }

    inline int TidStringLength()
    {
        return t_tidStringLength;
    }

    bool IsMainThread();


    struct MemProcInfo       //定义一个mem occupy的结构体
    {
        char name[20];      //定义一个char类型的数组名name有20个元素
        unsigned long mem;
        char name02[20];
    };

    struct MemInfo         //定义一个mem occupy的结构体
    {
        double mem_total;
        double mem_used_rate;
    };

    MemInfo GetMemoccupy();

    bool MemoryIsLow();

} //namespace emcache

#endif
