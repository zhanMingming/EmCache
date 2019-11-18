#ifndef EMCACHE_HASHHANDLE_H
#define EMCACHE_HASHHANDLE_H

#include"Entry.h"
#include"HashTable.h"


namespace emcache
{

    const int INIT_HASH_TABLE_SIZE = 8;

    class HandleTable
    {
    public:
        HandleTable(float load_factor_);
        ~HandleTable();

        Entry *Lookup(const Robj *key);
        Entry *Insert(Entry *key);

        Entry *Remove(const Robj *key);

        Entry  *RandomExpireKey();

    private:
        bool  IsRehashing()
        {
            return rehash_idx != -1;
        }

        void Resize();

        int ReHash(int step);

        int ReHashMilliseconds(int ms);

        // // 哈希表长度
        // uint32_t length_;
        // // 哈希表节点个数
        // uint32_t elems_;

        int32_t  rehash_idx;

        float  load_factor;

        HashTable  table[2];

    };

} //namespace emcache

#endif
