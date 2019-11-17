/*
* @Author: zhanmingming
* @Date:   2019-10-08 20:16:29
* @Last Modified by:   zhanmingming
* @Last Modified time: 2019-10-13 22:19:04
*/
#include "LRUCache.h"
#include<iostream>
#include<unistd.h>
#include"CacheOption.h"



using namespace std;
using namespace emcache;

int main() {
    CacheOption option;
    LRUCache  cache(option);
    //cache.SetCapacity(1024*1024);
    string key = "wode";
    string value = "val";

    for(int i = 0; i < 20; ++i) {
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

    cache.Set("iam", "ming", 1);
    sleep(2);
    std::cout << "after sleep" << std::endl;
    std::cout << cache.Get("iam") << std::endl;
    

}