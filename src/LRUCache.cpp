#include "LRUCache.h"
#include "Mutex.h"
#include "Util.h"
#include "System.h"
#include <glog/logging.h>
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
        DLOG(INFO) << option.toString();

        db = new DB(option.load_factor);

        lru.next = &lru;
        lru.prev = &lru;
    }

    LRUCache::~LRUCache()
    {
        DLOG(INFO) << "LRUCache~";
        if (db != nullptr)
        {
            DLOG(INFO) << "LRUCache~";
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

        //MutexLocker lock(mutex);
        WriteLockGuard  guard(lock);
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
        WriteLockGuard  guard(lock);
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
        ReadLockGuard guard(lock);
        Robj search(key);
        return db->dict->Lookup(&search);
    }



    bool LRUCache::ExpireKey(const std::string &key, int expire_time_)
    {
        
        Entry *entry = nullptr;
        if ((entry = LookupWithNotCheckExpire(key)) != nullptr)
        {
            WriteLockGuard guard(lock);
            int64_t expire_time = timeInSeconds() + expire_time_;
            Entry *expireEntry = new Entry(entry->key, expire_time);
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
        DLOG(INFO) << "DeleteKeyIfExpire";
        DLOG(INFO) << "v.s64:" << expire->v.s64;
        if (timeInSeconds() > expire->v.s64)
        {
            DLOG(INFO) << "delete " << expire->key->toString();
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

        WriteLockGuard  guard(lock);
        int num = db->expire_num;

        int del_expire_num = 0;
        DLOG(INFO) << "num:" << num;
        while (num > 0)
        {
            DLOG(INFO) << "RandomExpireKey";
            Entry  *entry = db->expire->RandomExpireKey();
            --num;
            DLOG(INFO) << "entry:" << entry;
            if (entry == nullptr)
            {
                continue;
            }

            while(entry != nullptr)
            {
                DLOG(INFO) << "remove key";
                Entry *next = entry->next_hash;
                DLOG(INFO) << "next:" << next;
                DLOG(INFO) << "remove key";

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