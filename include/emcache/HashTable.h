#ifndef EMCACHE_HASHTABLE_H
#define EMCACHE_HASHTABLE_H

#include "Entry.h"

namespace emcache {

class HandleTable;

class HashTable {
 public:
  friend class HandleTable;
  
  HashTable();
  ~HashTable();

  Entry* Lookup(const Robj*  key);
  Entry* Insert(Entry *key);
  Entry* Remove(const Robj* key);
  

  void Resize(int size);
  void Reset();
  void Free();

 private:
  Entry** FindPointer(const Robj* key);

  uint32_t HashFunc(const Robj* key);

  bool  NeedResize() {
      return elems_ > length_;
  }

  // 哈希表长度
  uint32_t length_;
  // 哈希表节点个数
  uint32_t elems_;

  Entry** list_;
};


}// namespace emcache

#endif

