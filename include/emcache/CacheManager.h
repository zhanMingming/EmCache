#ifndef EMCACHE_CACHE_MANAGER_H
#define EMCACHE_CACHE_MANAGER_H

#include <string>
#include <map>
#include <pthread.h>
#include <boost/shared_ptr.hpp>

namespace emcache
{

    class Cache;

    class CacheOption;

    class CacheManager
    {
    protected:
        CacheManager() {}
    public:
        ~CacheManager() {}
        CacheManager(const CacheManager &) = delete;
        CacheManager &operator=(const CacheManager &) = delete;

        boost::shared_ptr<Cache>  Create(const std::string &name, CacheOption option);

        static CacheManager *GetInstance();

        //static void Init();

        void AddCache(boost::shared_ptr<Cache> cache);

        boost::shared_ptr<Cache>  GetCache(const std::string &name);

    private:
        static void Init();

        std::map<std::string, boost::shared_ptr<Cache> >  mapping_cache;

        static pthread_once_t  once;

        static CacheManager  *instance;

    };

} //namespace emcache

#endif
