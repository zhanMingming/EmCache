#include "HashLRUCache.h"
#include "Hash.h"
#include "System.h"
#include "Util.h"

#include <boost/bind.hpp>
#include <glog/logging.h>
//#include <boost/protect.hpp>

namespace emcache
{

    HashLRUCache::HashLRUCache(const std::string &name_, CacheOption option)
        : name(name_)
    {

        db_num = option.db_num;
        assert(db_num > 0);
        //name = name_;

        if (option.maxmemory != -1)
        {
            const size_t per_capacity = (option.maxmemory + db_num - 1) / db_num;
            option.maxmemory = per_capacity;
        }

        shard  = new LRUCache*[db_num];
        for (int index = 0; index < db_num; ++index)
        {
            shard[index] = new LRUCache(option);
        }

        m_thread.reset(new CloseableThread(
                           boost::bind(&HashLRUCache::ThreadFunction, this, _1), boost::bind(&HashLRUCache::NotifyWhenThreadStop, this, _1)));
    }

    HashLRUCache::~HashLRUCache()
    {
        for(int index = 0; index < db_num; ++index)
        {
            delete shard[index];
        }
        delete[] shard;
        shard = nullptr;
        m_thread->Close();
    }


    bool HashLRUCache::Set(const std::string &key, const std::string &value, int expire_time)
    {
        DLOG(INFO) << "shardKey:" << Shard(key);
        return shard[Shard(key)]->Set(key, value, expire_time);
    }

    std::string HashLRUCache::Get(const std::string &key)
    {
        return  shard[Shard(key)]->Get(key);
    }

    uint32_t HashLRUCache::Shard(const std::string &key)
    {
        return  (Hash(key.data(), key.size(), 0) & (db_num - 1));
    }


    bool  HashLRUCache::ExpireKey(const std::string &key, int expire_time)
    {
        return  shard[Shard(key)]->ExpireKey(key, expire_time);
    }


    void HashLRUCache::DeleteKeyIfExpireCycle()
    {

        //uint64_t start = ustime();

        int total_expire_num = TotalExpireNum();
        int del_expire_num = 0;

        for(int pos = 0; pos < db_num; ++pos)
        {
            LRUCache  *cur = shard[pos];

            //int del_expire_num  =0;

            int num = cur->ExpireKeyNum();

            if (num == 0)
            {
                //cur->AvgTtl(0);
                continue;
            }

            // 获取键值对数量
            int slots = cur->Slots();
            DLOG(INFO) << "curDb:" << pos << " " 
                      << "ExpireKeyNum:" << cur->ExpireKeyNum() << " "
                      << "Slots:" << cur->Slots();

            // 如果 expireKey/ slots < 1%, 则先别扫描此db
            // if (!num || (slots < 100) || (num * 100 / slots < 1))
            // {
            //     DLOG(INFO) << "continue";
            //     continue;
            // }

            del_expire_num += cur->RandomRemoveExpireKey();
            if (del_expire_num > total_expire_num / 4)
            {
                break;
            }

        }
    }

    void HashLRUCache::ThreadFunction(const Function &checkFunc)
    {
        while(true)
        {
            checkFunc();

            DeleteKeyIfExpireCycle();
            
            DLOG(INFO) << "DeleteKeyIfExpireCycle 1 finish";
            if (MemoryIsLow())
            {
                DeleteKeyIfExpireCycle();
                DLOG(INFO) << "DeleteKeyIfExpireCycle 2 finish";

            }
            DLOG(INFO) << "start sleep";
            MicroSleep(1000);
            DLOG(INFO) << "end sleep";
        }

    }


    void HashLRUCache::NotifyWhenThreadStop(int threadId)
    {

    }

} //namespace emcache



