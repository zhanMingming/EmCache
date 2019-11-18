#ifndef EMCACHE_HASH_H
#define EMCACHE_HASH_H
#include<stdio.h>
#include<stdint.h>

namespace emcache
{

    uint32_t Hash(const char *data, size_t n, uint32_t seed);


} //namespace emcache

#endif
