#include <emcache/CacheManager.h>
#include <emcache/CacheOption.h>
#include <emcache/Cache.h>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace emcache;

int main() {
    boost::shared_ptr<CacheManager> manager(CacheManager::GetInstance());
    CacheOption option;
    manager->AddCache(manager->Create("AdInfo", option));

    boost::shared_ptr<Cache> cache =  manager->GetCache("AdInfo");

    string key = "key";
    string value = "val";

    for(int i = 0; i < 10000; ++i) {
        string key1 = key + to_string(i);
        string value1 = value + to_string(i);
        cache->Set(key1, value1, 100);
        //std::cout << "totalCharge:" << cache->TotalCharge() << std::endl;
    }
    key = "key";
    for (int i = 0; i < 10; ++i) {
        string key2 = key + to_string(i);
        std::cout << cache->Get(key2) << std::endl;
    }

    cache->Set("iam", "ming");
    std::cout << cache->Get("iam") << std::endl;
}