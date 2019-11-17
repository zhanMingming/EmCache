#ifndef EMCACHE_HASHLRUCACHE_H
#define EMCACHE_HASHLRUCACHE_H

#include "Cache.h"
#include "LRUCache.h"
#include "CacheOption.h"
#include "CloseableThread.h"

#include <stdint.h>
#include <boost/scoped_ptr.hpp>

namespace emcache
{

    //const int  db_num = 16;

    class HashLRUCache : public Cache
    {


    public:

        typedef CloseableThread::Function Function;
        HashLRUCache(const std::string &name_, CacheOption option);

        HashLRUCache(const HashLRUCache &) = delete;
        HashLRUCache &operator=(const HashLRUCache &) = delete;

        // Destroys all existing entries by calling the "deleter"
        // function that was passed to the constructor.
        ~HashLRUCache();


        bool Set(const std::string &key, const std::string &value, int expire_time = -1);


        std::string Get(const std::string &key);


        bool ExpireKey(const std::string &key, int expire_time);


        size_t TotalCharge() const
        {
            size_t total = 0;
            for (int pos = 0; pos < db_num; ++pos)
            {
                total += shard[pos]->TotalCharge();
            }
            return total;
        }

        size_t TotalExpireNum() const
        {
            size_t total = 0;
            for (int pos = 0; pos < db_num; ++pos)
            {
                total += shard[pos]->ExpireKeyNum();

            }
            return total;
        }

        void DeleteKeyIfExpireCycle();

        void  ThreadFunction(const Function &checkFunc);


        void  NotifyWhenThreadStop(int threadId);


        const std::string &Name() const
        {
            return name;
        }

    private:

        uint32_t Shard(const std::string &key);


        LRUCache  **shard;

        int db_num;

        const std::string name;

        boost::scoped_ptr<CloseableThread> m_thread; // Thread must be the last variable



        //uint64_t  last_id;
    };

} //namespace emcache

#endif



