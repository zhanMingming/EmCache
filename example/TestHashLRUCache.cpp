#include "HashLRUCache.h"
#include <iostream>
#include <unistd.h>
#include "CacheOption.h"
#include <gflags/gflags.h>
#include <glog/logging.h>



using namespace std;
using namespace emcache;

int main(int argc, char **argv) {

    google::InitGoogleLogging(argv[0]);  // 初始化 glog
    google::ParseCommandLineFlags(&argc, &argv, true);  // 初始化 gflags
    FLAGS_log_dir = "./log";
    FLAGS_max_log_size = 10;
    //google::SetLogDestination(google::GLOG_INFO, FLAGS_log_dir);
    google::SetStderrLogging(google::GLOG_INFO);


    CacheOption  option;
    HashLRUCache  cache("wode", option);

    string key = "wode";
    string value = "val";

    for(int i = 0; i < 10000; ++i) {
        string key1 = key + to_string(i);
        string value1 = value + to_string(i);
        cache.Set(key1, value1, 100);
        //std::cout << "totalCharge:" << cache.TotalCharge() << std::endl;
    }
    key = "wode";
    for (int i = 0; i < 10; ++i) {
        string key2 = key + to_string(i);
        //std::cout << cache.Get(key2) << std::endl;
    }

    cache.Set("iam", "ming");
    sleep(2);
    std::cout << cache.Get("iam") << std::endl;
    google::ShutdownGoogleLogging();


}