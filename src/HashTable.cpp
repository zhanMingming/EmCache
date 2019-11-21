#include "HashTable.h"
#include "Hash.h"
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
// #include <glog/logging.h>
#include <string>


using namespace std;

namespace emcache
{

    class Robj;

    bool compartor(const Robj *x, const Robj *y)
    {
        return x->operator==(y);
    }

    HashTable::HashTable() : length_(0), elems_(0), list_(nullptr) {}
    HashTable::~HashTable()
    {
        Free();
    }

    uint32_t HashTable::HashFunc(const Robj *key)
    {
        return Hash(key->data(), key->length(), 1024);
    }

    Entry *HashTable::Lookup(const Robj *key)
    {
        return *FindPointer(key);
    }

    Entry *HashTable::Insert(Entry *h)
    {
        //std::cout << h->key->toString() << std::endl;
        Entry **ptr = FindPointer(h->key);
        Entry *old = *ptr;
        //如果*ptr != null, 则证明已有相同节点存在, 将*ptr 赋值为h
        //如果*ptr == null, 则在末尾插入h 节点。
        h->next_hash = (old == nullptr ? nullptr : old->next_hash);
        *ptr = h;

        // old 节点为空，代表没有相同节点，插入了新节点
        if (old == nullptr)
        {
            ++elems_;
            // if (elems_ > length_) {
            // // Since each cache entry is fairly large, we aim for a small
            // // average linked list length (<= 1).
            //     Resize();
            // }
        }

        return old;
    }

    Entry *HashTable::Remove(const Robj *key)
    {
        Entry **ptr = FindPointer(key);
        Entry *result = *ptr;
        if (result != nullptr)
        {
            *ptr = result->next_hash;
            --elems_;
        }
        return result;
    }

    Entry **HashTable::FindPointer(const Robj *key)
    {
        uint32_t hash = HashFunc(key);
        Entry **ptr = &list_[hash & (length_ - 1)];
        while ((*ptr != nullptr) && !(compartor((*ptr)->key, key)))
        {
            ptr = &(*ptr)->next_hash;
        }
        return ptr;
    }

    void HashTable::Reset()
    {
        length_ = 0;
        elems_ = 0;
        list_ = nullptr;
    }

    // void PrintInfo(Entry** list, int size) {
    //     std::string info = "Resize:list:" + to_string(size) + ": ";
    //     for (int index = 0; index < size; ++index) {
    //         info += to_string((uint64_t)list[index]);
    //         info += ":";
    //     }
    //     DLOG(INFO) << info;

    // }
    void HashTable::Resize(int size)
    {

        Entry **new_list = new Entry*[size];
        memset(new_list, 0, sizeof(new_list[0]) * size);
        list_ = new_list;
        length_ = size;
    }

    void HashTable::Free()
    {

        for (int index = 0; index < length_; ++index)
        {
            Entry *h = list_[index];
            while (h != nullptr)
            {
                Entry *next = h->next_hash;
                delete h;
                h = next;
            }
            list_[index] = nullptr;
        }
        if (list_)
        {
            delete[] list_;
        }
        list_ = nullptr;
    }


} //namespace emcache

