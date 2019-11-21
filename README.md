[中文版](https://github.com/zhanMingming/EmCache/blob/master/README_CN.md)
## I. Introduction

Emcache is a local high-performance cache library implemented by C++. The underlying core data structure is a hash table,The main design ideas are as follows:

- Automatic expansion of hash table

- Automatic capacity expansion adopts progressive hashing to avoid performance jitter caused by centralized re hashing.

- Support setting key expiration time

- Support setting cache size. If maxmemory is not set, LRU elimination strategy will be adopted automatically in case of memory shortage

- Processing method of expired key: inert deletion + regular deletion.


## II.Linux system installation

EmCache depends on boost library 1.54.0+, GCC 4.8+, cmake 3.0+

### Installation dependency


###### Install compilation tools
```
yum install gcc-c++ make  git 

```

###### Install cmake version 3.12

```
#cmake ：https://cmake.org/files/

wget https://cmake.org/files/v3.12/cmake-3.12.0.tar.gz
tar xzvf cmake-3.12.0.tar.gz
cd cmake-3.12.0
./bootstrap
gmake
make install

```
###### Install boost version 1.71.0
```
wget https://dl.bintray.com/boostorg/release/1.71.0/source/boost_1_71_0.tar.gz

tar -zxvf boost_1_71_0.tar.gz

cd boost_1_71_0 

./bootstrap.sh  --with-libraries=all && ./b2 && ./b2 isntall

```

### Install EmCache

```
git clone https://github.com/zhanMingming/EmCache.git

cd EmCache/

mkdir build && cd build

cmake ..

make && make install

```

## III: Usage

#### CacheOption
```
enum  LruOption
{
    //Use LRU algorithm to eliminate data, only key with expiration time set
    volatile_lru = 0,
    //All keys can be eliminated by using LRU algorithm
    allkeys_lru
};
    
struct CacheOption
{
    //Elimination strategy
    LruOption  lru;
        
    // Maximum memory  MB
    int maxmemory;

    //Maximum key length KB
    int max_key_length;

    //Maximum value length KB
    int max_value_length;

    //If the load factor is greater than this value (generally set to 1.0), capacity expansion will begin
    float load_factor;

    //The number of DB is recommended to be set as the number of CPU cores
    //In order to achieve high performance, emcache uses multiple hash tables at the bottom,
    //which reduces the competition for locks in a multithreaded environment
    int db_num = 16;
};


```

#### CacheManager

```
//Get Single Instance
CacheManager *cache = CacheManager::GetInstance();

//Cache option, the default option is used here
CacheOption  option1;

// Create a cache named AdInfo
boost::shared_ptr<Cache>  adInfoCache = manager->Create("AdInfo", option1);

CacheOption option2;

//Create a cache named IndexInfo
boost::shared_ptr<Cache> indexInfoCache = manager->Create("IndexInfo", option2);
```
In the design of emcache, we can use different cacheoption classes to create cache objects with different properties. For example, in the advertising business scenario, we can use different cache objects for advertising data and index data.

#### Cache
Generally speaking, we can create the cache object we need in the main thread.
```
// Main Thread

CacheManager *cache = CacheManager::GetInstance();

CacheOption option;
boost::shared_ptr<Cache>  adInfoCache = manager->Create("AdInfo", option);


cache->AddCache(adInfoCache);

```

Get the cache object in the worker thread for set, get and other operations.

```
// Worker Thread

boost::shared_ptr<Cache> adInfoCache = cache->GetCache("AdInfo");

// Insert the key and set the expiration time to 100 seconds
adInfoCache->Set("key", "value",  100);

string val = adInfoCache->Get("key");

```

