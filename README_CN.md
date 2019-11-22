## 一.介绍
Emcache 是一个c++实现的本地高性能缓存库。底层核心数据结构是哈希表，
主要设计思路如下：

- 哈希表表自动扩容

- 自动扩容采用渐进式哈希, 避免集中式重哈希带来的性能抖动。

- 支持设置key 过期时间

- 支持设置缓存大小，如果未设置maxmemory, 则内存紧张时，自动采用LRU淘汰策略

- 过期key 处理方法：采用惰性删除+定期删除的方式。


## 二.Linux 系统下安装

Emcache 依赖 Boost库1.54.0版本及以上、GCC 4.8及以上、CMake 3.0 版本及以上

### 安装依赖


###### 安装编译工具
```
yum install gcc-c++ make  git 

```

###### 安装 cmake 3.12版本

```
#cmake 提供的下载地址为：https://cmake.org/files/

wget https://cmake.org/files/v3.12/cmake-3.12.0.tar.gz
tar xzvf cmake-3.12.0.tar.gz
cd cmake-3.12.0
./bootstrap
gmake
make install

```
###### 安装 boost 1.71.0 版本
```
wget https://dl.bintray.com/boostorg/release/1.71.0/source/boost_1_71_0.tar.gz

tar -zxvf boost_1_71_0.tar.gz

cd boost_1_71_0 

./bootstrap.sh  --with-libraries=all && ./b2 && ./b2 isntall

```

### 安装Emcache

```
git clone https://github.com/zhanMingming/Emcache.git

cd Emcache/

mkdir build && cd build

cmake ..

make && make install

```

## 三：用法

#### CacheOption类的使用
```
enum  LruOption
{
    //使用LRU算法进行数据淘汰，只淘汰设置了过期时间的key
    volatile_lru = 0,
    //使用LRU算法进行数据淘汰，所有的key都可以被淘汰；
    allkeys_lru
};
    
struct CacheOption
{
    //具体淘汰策略
    LruOption  lru;
        
    // 最多使用内存 单位：MB
    // 值为0 代表 无限制
    int maxmemory;

    //最大KEY的长度 单位：KB
    // 默认值为 521KB
    int max_key_length;

    //最大Value的长度 单位：KB
    // 默认值为 1024KB
    int max_value_length;

    //负载因子 大于此值(一般设置为1.0) 开始扩容
    //默认值为1.0
    float load_factor;

    //db数量, 这里推荐设置为CPU核心数
    //Emcache为了高性能, 底层采用了多个哈希表，在多线程环境下减少了对锁的竞争
    //默认值为16
    int db_num;
};

```

#### CacheManager的用法

```
//获取单例
CacheManager *cache = CacheManager::GetInstance();

//cache 选项，此处此用默认选项
CacheOption  option1;

// 构造名为AdInfo 的 Cache
boost::shared_ptr<Cache>  adInfoCache = manager->Create("AdInfo", option1);

CacheOption option2;

//构造名为IndexInfo 的Cache
boost::shared_ptr<Cache> indexInfoCache = manager->Create("IndexInfo", option2);
```
在Emcache的设计中，我们可以用不同的CacheOption类去创建成不同属性的Cache对象。比如在广告业务场景中，我们可以对广告数据 以及索引数据 使用不同的缓存对象。


#### Cache 的用法
一般来说我们可以在主线程中创建我们需要的Cache对象
```
// Main Thread

CacheManager *cache = CacheManager::GetInstance();

CacheOption option;
boost::shared_ptr<Cache>  adInfoCache = manager->Create("AdInfo", option);


cache->AddCache(adInfoCache);

```

在工作线程中获取Cache对象进行SET, GET 等操作

```
// Worker Thread

boost::shared_ptr<Cache> adInfoCache = cache->GetCache("AdInfo");

// 插入key, 并设置过期时间为100秒
// 过期时间 单位：秒
adInfoCache->Set("key", "value",  100);

string val = adInfoCache->Get("key");

```

