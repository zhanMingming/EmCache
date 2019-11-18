#ifndef EMCACHE_CACHE_OPTION
#define EMCACHE_CACHE_OPTION
#include<string>
/*
volatile-lru：使用LRU算法进行数据淘汰（淘汰上次使用时间最早的，且使用次数最少的key），只淘汰设定了有效期的key ；
allkeys-lru：使用LRU算法进行数据淘汰，所有的key都可以被淘汰；
volatile-random：随机淘汰数据，只淘汰设定了有效期的key；
allkeys-random：随机淘汰数据，所有的key都可以被淘汰；
volatile-ttl：淘汰剩余有效期最短的key；
no-enviction：不删除任意数据(但redis还会根据引用计数器进行释放),这时如果内存不够时，会直接返回错误 。
 */

namespace emcache
{


    enum  LruOption
    {
        volatile_lru = 0,
        allkeys_lru,
    };

    struct CacheOption
    {

        LruOption  lru = volatile_lru;

        //单位KB，

        int maxmemory = -1;


        int max_key_length =  521;



        int max_value_length = 1024;


        //负载因子 大于此值， 开始扩容
        float load_factor = 2.0;

        //DB 数量  一般可以和cpu core 想等
        int db_num = 16;


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
