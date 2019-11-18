#include "LRUCache.h"
#include "Mutex.h"
#include "Util.h"
#include "System.h"
#include <string>
#include <sys/time.h>
#include <stdint.h>
#include <iostream>

using namespace std;

namespace emcache
{

    LRUCache::LRUCache(CacheOption option_)
        : option(option_), usage(0)
    {
        assert(option.load_factor > 0);

        option.max_key_length = option.max_key_length == -1 ? MAX_KEY_LENGTH : option.max_key_length;
        option.max_value_length = option.max_value_length == -1 ? MAX_VALUE_LENGTH : option.max_value_length;
        // Make empty circular linked lists.
        std::cout << option.toString();

        db = new DB(option.load_factor);

        lru.next = &lru;
        lru.prev = &lru;

    }

    LRUCache::~LRUCache()
    {
        std::cout << "LRUCache~" << std::endl;
        if (db != nullptr)
        {
            std::cout << "LRUCache~" << std::endl;
            delete db;
            db = nullptr;
        }
    }


    bool LRUCache::Set(const std::string &key,  const std::string &value,  int expire_time)
    {
        if (key.size() > option.max_key_length  || value.size() > option.max_value_length)
        {
            return false;
        }

        return Insert(key, value, expire_time);

    }

    std::string LRUCache::Get(const std::string &key)
    {
        Entry *ret = Lookup(key);
        if (!ret)
        {
            std::cout << "ret null" << std::endl;
            return string("");
        }
        return ret->v.val->toString();
    }


    bool LRUCache::Insert(const string &key, const string &value, int expire_time_)
    {
        //std::cout << "Lru:" << capacity <<  std::endl;
        //capacity = 1024*1024;

        MutexLocker lock(mutex);
        //assert(capacity > 0);
        //分配结点
        Entry *newEntry = new Entry(key, value);

        FinishErase(db->dict->Insert(newEntry));
        ++db->slots;
        LRUAppend(&lru, newEntry);
        usage += key.length();
        usage += value.length();

        if(expire_time_ != -1)
        {
            int64_t expire_time = timeInSeconds() + expire_time_;
            Entry  *expireEntry = new Entry(newEntry->key, expire_time);
            FinishErase(db->expire->Insert(expireEntry));
            ++db->expire_num;
        }

        if ((option.maxmemory == -1 && MemoryIsLow()) || (option.maxmemory != -1 && usage > option.maxmemory))
        {

            LRUEliminate(option.lru);
        }

        return true;
    }


    Entry *LRUCache::Lookup(const std::string &key)
    {
        // need ToDo delete search
        Robj search(key);
        Entry  *t =  db->expire->Lookup(&search);

        if (t)
        {
            if (DeleteKeyIfExpire(t))
            {
                return nullptr;
            }
        }
        return db->dict->Lookup(&search);
    }

    Entry *LRUCache::LookupWithNotCheckExpire(const std::string &key)
    {
        Robj search(key);
        return db->dict->Lookup(&search);
    }



    bool LRUCache::ExpireKey(const std::string &key, int expire_time_)
    {
        Entry *entry = nullptr;
        if ((entry = LookupWithNotCheckExpire(key)) != nullptr)
        {
            int64_t expire_time = timeInSeconds() + expire_time_;
            Entry *expireEntry = new Entry(entry->key, expire_time);

            // 这个锁 需要优化
            MutexLocker lock(mutex);
            FinishErase(db->expire->Insert(expireEntry));
            ++db->expire_num;
            return true;
        }
        return false;
    }


    void LRUCache::LRUAppend(Entry *list, Entry *p)
    {
        p->next = list;
        p->prev = list->prev;
        p->prev->next = p;
        p->next->prev = p;
    }

    bool LRUCache::DeleteKeyIfExpire(Entry *expire)
    {
        if (timeInSeconds() > expire->v.s64)
        {
            std::cout << expire->key->toString() << std::endl;
            // 这个锁 需要优化
            MutexLocker lock(mutex);
            FreeEntry(expire);
            return true;
        }
        return false;
    }

    void LRUCache::LRURemove(Entry *p)
    {
        p->next->prev = p->prev;
        p->prev->next = p->next;
    }

    void LRUCache::LRUEliminate(LruOption type)
    {

        //当插入Key之后，发现所用空间> caapacity时，需要释放空间
        // Todo  需要 优化
        // Mac 系统下 目前没有设置maxmemory的话，当内存紧张时 无法回收内存
        while (option.maxmemory != -1 && usage > option.maxmemory && lru.next != &lru)
        {
            Entry *old = lru.next;
            FreeEntry(old);
            usage -= old->key->len;
            usage -= old->v.val->len;
        }

        while (MemoryIsLow() && lru.next != &lru) {
            Entry *old = lru.next;
            FreeEntry(old);
            usage -= old->key->len;
            usage -= old->v.val->len;
        }

    }


    void LRUCache::FreeEntry(Entry *del)
    {

        Entry *dictDel = db->dict->Remove(del->key);

        if (dictDel)
        {
            LRURemove(dictDel);
            --db->slots;
            FinishErase(dictDel);
        }

        Entry *expireDel = db->expire->Remove(del->key);

        if (expireDel)
        {
            --db->expire_num;
            FinishErase(expireDel);
        }
    }
    /*
    redis.c/activeExpireCycle
    */

    int LRUCache::RandomRemoveExpireKey()
    {

        int num = db->expire_num;

        int del_expire_num = 0;
        while (num--)
        {
            std::cout << "RandomExpireKey" << std::endl;
            Entry  *entry = db->expire->RandomExpireKey();
            if (entry == nullptr)
            {
                continue;
            }
            while(entry != nullptr)
            {
                Entry *next = entry->next_hash;
                if (DeleteKeyIfExpire(entry))
                {
                    ++del_expire_num;
                }
                entry = next;
            }
        }
        return del_expire_num;
    }

    void LRUCache::FinishErase(Entry *p)
    {
        if (p)
        {
            delete p;
            p = nullptr;
        }
    }

} //namespace emcache