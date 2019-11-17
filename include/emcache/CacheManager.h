#ifndef EMCACHE_CACHE_MANAGER_H
#define EMCACHE_CACHE_MANAGER_H

#include<string>
#include<map>
#include<pthread.h>

namespace emcache
{

    class Cache;

    class CacheOption;

    class CacheManager
    {

    protected:
        CacheManager() {};

    public:
        ~CacheManager();
        CacheManager(const CacheManager &) = delete;
        CacheManager &operator=(const CacheManager &) = delete;

        Cache *Create(const std::string &name, CacheOption option);

        static CacheManager *GetInstance();

        //static void Init();

        void AddCache(Cache *cache);

        Cache *GetCache(const std::string &name);


    private:
        static void Init();

        std::map<std::string, Cache *>  mapping_cache;

        static pthread_once_t  once;

        static CacheManager  *instance;

    };



} //namespace emcache




#endif
