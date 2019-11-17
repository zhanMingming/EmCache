/*
* @Author: zhanmingming
* @Date:   2019-10-09 19:18:38
* @Last Modified by:   zhanmingming
* @Last Modified time: 2019-10-13 22:29:18
*/

#include "HashLRUCache.h"
#include<iostream>
#include<unistd.h>
#include"CacheOption.h"


using namespace std;
using namespace emcache;

int main() {
    CacheOption  option;
    HashLRUCache  cache("wode", option);

    string key = "wode";
    string value = "val";

    for(int i = 0; i < 10000; ++i) {
        string key1 = key + to_string(i);
        string value1 = value + to_string(i);
        cache.Set(key1, value1, 100);
        std::cout << "totalCharge:" << cache.TotalCharge() << std::endl;
    }
    key = "wode";
    for (int i = 0; i < 10; ++i) {
        string key2 = key + to_string(i);
        std::cout << cache.Get(key2) << std::endl;
    }

    cache.Set("iam", "ming");
    sleep(2);
    std::cout << cache.Get("iam") << std::endl;
    

}