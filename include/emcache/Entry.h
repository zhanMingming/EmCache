#ifndef EMCACHE_ENTRY_H_
#define EMCACHE_ENTRY_H_

#include <stdint.h>
#include <string>
#include <string.h>
#include <cstdio>
#include<iostream>

namespace emcache {

struct Robj {

    Robj(const std::string& str) {
        len = str.length();
        buf = new char[str.length() + 1];
        memcpy(buf, str.data(), str.length());
        buf[len] = 0;
        count = new int16_t(1);
    }


    Robj(const Robj* rhs)
    :len(rhs->len), buf(rhs->buf), count(rhs->count)
    {
        ++(*count);
    }
    

    // Robj():len(0), buf(nullptr) {}
    
    ~Robj() {
        //std::cout << "free Robj" << std::endl;
        if (--(*count) == 0) {
            delete[] buf;
            buf = nullptr;

            delete[] count;
            count = nullptr;

            //std::cout << "real free Robj" << std::endl;
        }
    }

    bool operator==(const Robj* x) const {
        return ((x->size() == size()) && 
           (memcmp(x->data(), data(), x->size()) == 0));
    }

    int size()  const {
        return len;
    }
    int length() const {
        return len;
    }

    std::string toString() {
        return std::string(buf, len);
    }

    const char* data() const {
        return buf;
    }

    //length
    int len;

    //data
    char* buf;

    //引用计数
    int16_t *count;
};


// bool operator==(const Robj& x, const Robj& y) {
//   return ((x.size() == y.size()) &&
//           (memcmp(x.data(), y.data(), x.size()) == 0));
// }

// bool operator!=(const Robj& x, const Robj& y) { return !(x == y); }

// bool compartor(const Robj*x, const Robj* y) {
//     return x->operator==(y);
// }


// bool operator==(const Robj* x, const Robj* y) {
//     return x->operator==(y);
// }

// bool operator!=(const Robj* x, const Robj* y) { return !(x==y);}


// Entry 的设计

struct Entry {

    Entry(const std::string& key_,  const std::string& value_) {
        key = new Robj(key_);
        v.val = new Robj(value_);
        flag = true;
    }


    Entry(Robj* key_, int64_t expire_time)
    {
        key = new Robj(key_);
        v.s64 = expire_time;
        flag = false;
    }

    Entry() {
        key = nullptr;
        v.val = nullptr;
        next_hash = nullptr;
        next = nullptr;
        prev = nullptr;
        flag = true;
    }

    ~Entry() {
        //std::cout << "key:" << key << std::endl;
        if (key) {
            delete key;
            key = nullptr;
            //std::cout << "free key" << std::endl;
        }
        if (v.val && flag) {
            delete v.val;

            v.val = nullptr;
            //std::cout << "free v.val" << std::endl;
        }
    }

    Robj* key;

    union {
        Robj* val;
        int64_t s64;
    }v;

    Entry* next_hash;

    Entry* next;
    Entry* prev;
    bool flag;
};


} //namespace emcache


#endif
