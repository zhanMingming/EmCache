
#include"CacheManager.h"
#include"Cache.h"
#include"HashLRUCache.h"
#include"CacheOption.h"


using namespace std;

namespace emcache {


CacheManager*  CacheManager::instance = nullptr;

pthread_once_t CacheManager::once = PTHREAD_ONCE_INIT;

void CacheManager::Init() {
    instance = new CacheManager();
}

CacheManager* CacheManager::GetInstance() {
    pthread_once(&once, Init);
    return instance;
}


Cache*  CacheManager::Create(const std::string& name, CacheOption option) {
    Cache* cache = new HashLRUCache(name, option);
    return cache;
}



void CacheManager::AddCache(Cache* cache) {
    mapping_cache.insert(make_pair(cache->Name(), cache));
}


Cache* CacheManager::GetCache(const string& name) {
    map<string, Cache*>::iterator  pair = mapping_cache.find(name);
    if (pair != mapping_cache.end()) {
        return pair->second;
    } 
    return nullptr;
}


} //namespace emcache



