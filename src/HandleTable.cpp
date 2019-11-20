#include "HandleTable.h"
#include "Entry.h"
#include "Util.h"
#include <sys/time.h>
#include <stdlib.h>
#include <iostream>
#include <glog/logging.h>

using namespace std;

namespace emcache
{

    HandleTable::HandleTable(float load_factor_)
        : rehash_idx(-1), load_factor(load_factor_)
    {
        table[0].Resize(INIT_HASH_TABLE_SIZE);
    }

    HandleTable::~HandleTable()
    {
        DLOG(INFO) << "~HandleTable";
    }


    Entry *HandleTable::Lookup(const Robj *key)
    {
        if (IsRehashing())
        {
            Entry *p = table[1].Lookup(key);
            if (p)
            {
                return p;
            }
            else
            {
                p = table[0].Lookup(key);
            }
            return p;
        }

        return table[0].Lookup(key);
    }



    Entry *HandleTable::Insert(Entry *key)
    {
        //std::cout << "HandleTable Insert" << std::endl;
        Entry *old = nullptr;
        if (IsRehashing())
        {
            old = table[1].Insert(key);
            ReHash(1);
        }
        else
        {
            old = table[0].Insert(key);
            if (table[0].length_  * load_factor  >  table[0].elems_)
            {
                Resize();
            }
        }
        return old;
    }


    Entry *HandleTable::Remove(const Robj *key)
    {
        Entry *result = nullptr;
        if (IsRehashing())
        {
            result = table[1].Remove(key);
            if (result)
            {
                return result;
            }
            // } else {
            //     result = table[1].Remove(key);
            // }
            // return result;
        }
        return table[0].Remove(key);
    }

    /**
     * return num of removeExpireKey
     */

    Entry *HandleTable::RandomExpireKey()
    {
        Entry *rand_entry = nullptr;
        int rand_num = 0;

        if (IsRehashing())
        {
            rand_num = random() % table[1].length_;
            DLOG(INFO) << "rand_num:" << rand_num << " " << "table1.length" << table[1].length_;
            rand_entry = table[0].list_[rand_num] != nullptr ? table[0].list_[rand_num] : table[1].list_[rand_num];

        }
        else
        {
            rand_num = random() % table[0].length_;
            DLOG(INFO) << "rand_num:" << rand_num << " " << "table1.length" << table[0].length_;

            rand_entry = table[0].list_[rand_num];
        }

        return rand_entry;
    }

    void HandleTable::Resize()
    {
        if (IsRehashing())
        {
            return;
        }
        table[1].Resize(table[0].length_ * 2);
        rehash_idx = 0;
        ReHash(1);
    }


    int  HandleTable::ReHash(int step)
    {

        if (rehash_idx < 0) return 0;
        while(step--)
        {


            if (table[0].elems_ == 0)
            {

                table[0].Free();

                table[0] = table[1];

                table[1].Reset();

                rehash_idx = -1;

                return 0;
            }

            assert(table[0].length_ > (uint32_t)rehash_idx);

            while(table[0].list_[rehash_idx] == nullptr)  rehash_idx++;

            Entry *p = table[0].list_[rehash_idx];

            while(p)
            {

                Entry *next = p->next_hash;


                table[1].Insert(p);

                --table[0].elems_;

                p = next;
            }

            table[0].list_[rehash_idx] = nullptr;
            rehash_idx++;
        }
        return 1;
    }



    /*
     在给定毫秒数内，以 100 步为单位，对字典进行 rehash 。
    */
    int HandleTable::ReHashMilliseconds(int ms)
    {
        // 记录开始时间
        long long start = timeInMilliseconds();
        int rehashes = 0;

        while(ReHash(100))
        {
            rehashes += 100;
            // 如果时间已过，跳出
            if (timeInMilliseconds() - start > ms) break;
        }

        return rehashes;
    }

}// namespace emcache

