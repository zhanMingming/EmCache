#include "CacheManager.h"
#include "CacheOption.h"
#include "Cache.h"

#include <iostream>
#include <unistd.h>
#include <glog/logging.h>
#include <gflags/gflags.h>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace emcache;

int main(int argc, char **argv) {
    google::InitGoogleLogging(argv[0]);  // 初始化 glog
    google::ParseCommandLineFlags(&argc, &argv, true);  // 初始化 gflags
    FLAGS_log_dir = "./log";
    FLAGS_max_log_size = 10;
    //google::SetLogDestination(google::GLOG_INFO, FLAGS_log_dir);
    google::SetStderrLogging(google::GLOG_INFO);

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
    sleep(2);
    std::cout << cache->Get("iam") << std::endl;
    //delete cache;
    google::ShutdownGoogleLogging();
}