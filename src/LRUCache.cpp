#include "LRUCache.h"
#include "Mutex.h"
#include "Util.h"
#include "System.h"
// #include <glog/logging.h>
#include <string>
#include <sys/time.h>
#include <stdint.h>
#include <iostream>

using namespace std;

namespace emcache
{

    LRUCache::LRUCache(CacheOption option_)
        : usage(0), option(option_)
    {
        assert(option.load_factor > 0);

        option.max_key_length = option.max_key_length == 0 ? MAX_KEY_LENGTH : option.max_key_length;
        option.max_value_length = option.max_value_length == 0 ? MAX_VALUE_LENGTH : option.max_value_length;
        // Make empty circular linked lists.
        db = new DB(option.load_factor);

        lru.next = &lru;
        lru.prev = &lru;
    }

    LRUCache::~LRUCache()
    {
        if (db != nullptr)
        {
            delete db;
            db = nullptr;
        }
    }

    bool LRUCache::Set(const std::string &key,  const std::string &value,  int expire_time)
    {
        if ((key.size() / 1024)> option.max_key_length  || (value.size()/1024) > option.max_value_length)
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
            return string("");
        }
        return ret->v.val->toString();
    }

    bool LRUCache::Insert(const string &key, const string &value, int expire_time_)
    {

        MutexLocker lock(mutex);
        //WriteLockGuard  guard(lock);
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
        std::cout << "insert key" << "[" << key  << ":" << value << std::endl;

        if ((option.maxmemory == 0 && MemoryIsLow()) || (option.maxmemory != 0 && usage > option.maxmemory))
        {
            LRUEliminate(option.lru);
        }

        return true;
    }

    Entry *LRUCache::Lookup(const std::string &key)
    {
        // need ToDo delete search
        //WriteLockGuard  guard(lock);
        MutexLocker lock(mutex);
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
        //ReadLockGuard guard(lock);
        // MutexLocker lock(mutex);
        Robj search(key);
        return db->dict->Lookup(&search);
    }

    bool LRUCache::ExpireKey(const std::string &key, int expire_time_)
    {
        MutexLocker  lock(mutex);
        Entry *entry = nullptr;
        if ((entry = LookupWithNotCheckExpire(key)) != nullptr)
        {
            //WriteLockGuard guard(lock);
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
        // DLOG(INFO) << "DeleteKeyIfExpire";
        // DLOG(INFO) << "key:" << expire->key->toString();

        // DLOG(INFO) << "v.s64:" << expire->v.s64;
        if (timeInSeconds() > expire->v.s64)
        {
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
        while (option.maxmemory != 0 && usage > option.maxmemory && lru.next != &lru)
        {
            std::cout << "LRU1" << std::endl;
            Entry *old = lru.next;
            usage -= old->key->len;
            usage -= old->v.val->len;
            FreeEntry(old);
        }

        while (MemoryIsLow() && lru.next != &lru) {
            std::cout << "LRU2" << std::endl;
            Entry *old = lru.next;
            usage -= old->key->len;
            usage -= old->v.val->len;
            FreeEntry(old);
        }
    }

    void LRUCache::FreeEntry(Entry *del)
    {
        std::cout << del->key->toString() << std::endl;
        Entry *dictDel = db->dict->Remove(del->key);

        // if (dictDel)
        // {
        //     LRURemove(dictDel);
        //     --db->slots;
        //     FinishErase(dictDel);
        // }
        std::cout << "expire remove" << std::endl;
        std::cout << del->key << std::endl;
        std::cout << "delkey:" << del->key->toString() << std::endl;
        Entry *expireDel = db->expire->Remove(del->key);

        if (dictDel)
        {
            LRURemove(dictDel);
            --db->slots;
            std::cout << "dict erase" << std::endl;
            FinishErase(dictDel);
        }

        if (expireDel)
        {
            --db->expire_num;
            std::cout << "expire erase" << std::endl;

            FinishErase(expireDel);
        }
    }
    /*
    redis.c/activeExpireCycle
    */
    // void PrintInfo(Entry* entry) {
    //     std::string info = "";
    //     DLOG(INFO) << "key:" << entry->key->toString() << " value:" << to_string(entry->v.s64);
    //     DLOG(INFO) << "next_hash:" << entry->next_hash;
    //     if (entry->next_hash != nullptr) {
    //         DLOG(INFO) << "not equal";
    //     }
    //     while(entry != nullptr) {
    //         Entry* next = entry->next_hash;
    //         info += entry->key->toString();
    //         info += to_string(entry->v.s64);
    //         entry = next;
    //     }
    //     DLOG(INFO) << "info:" << info;
    // }

    int LRUCache::RandomRemoveExpireKey()
    {
        MutexLocker  lock(mutex);
        //WriteLockGuard  guard(lock);
        size_t num = db->expire_num;

        int del_expire_num = 0;
        while (num > 0)
        {
            Entry  *entry = db->expire->RandomExpireKey();
            --num;
            // DLOG(INFO) << "entry:" << entry;
            // DLOG(INFO) << "entry_64:" << (uint64_t)entry;
            if (entry == nullptr)
            {
                continue;
            }
            //PrintInfo(entry);

            while(entry != nullptr)
            {
                // DLOG(INFO) << "remove key";
                Entry *next = entry->next_hash;
                // DLOG(INFO) << "next:" << next;
                // DLOG(INFO) << "remove key";

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