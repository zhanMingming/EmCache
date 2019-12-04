#ifndef EMCACHE_CACHE_OPTION
#define EMCACHE_CACHE_OPTION
#include <string>
/*
volatile-lru：Use LRU algorithm to eliminate data (eliminate the key with the earliest last use time and the least use times), and only eliminate the key with set validity period
allkeys-lru：All keys can be eliminated by using LRU algorithm
 */

namespace emcache
{
    enum  LruOption
    {
        volatile_lru = 0,
        allkeys_lru
    };

    struct CacheOption
    {

        LruOption  lru = volatile_lru;
        
        // A value of 0 means unlimited  Unit：MB
        size_t maxmemory = 0;

        // max key length  Unit: KB
        size_t max_key_length =  521;
        
        //max value length  Unit: KB
        size_t max_value_length = 1024;

        //when the load_factor reaches the set value, capacity expansion start
        float load_factor = 1.0;

        //The number of DB is recommended to be set as the number of CPU cores
        //In order to achieve high performance, emcache uses multiple hash tables at the bottom,
        //which reduces the competition for locks in a multithreaded environment
        size_t db_num = 16;

        std::string toString()
        {
            return  std::string("lru:") + std::to_string(lru) + "\t" +
                    "maxmemory:" + std::to_string(maxmemory) + "\t" +
                    "max_key_length:" + std::to_string(max_key_length) + "\t" +
                    "max_value_length:" + std::to_string(max_value_length) + "\t" +
                    "load_factor:" + std::to_string(load_factor) + "\t" +
                    "db_num:" + std::to_string(db_num) + "\n";
        }
    };

} //endif

#endif
