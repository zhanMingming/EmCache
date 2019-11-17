#include"HashTable.h"
#include"Entry.h"
#include<string>
#include<iostream>

using namespace std;
using namespace emcache;

int main() {
    HashTable handle;
    handle.Resize(1024);
    string key = "wode";
    string value = "val";

    for(int i = 0; i < 10000; ++i) {
        string key1 = key + to_string(i);
        string value1 = value + to_string(i);
        Entry *h = new Entry(key1, value1);
        std::cout << "insert:" << h->key->toString() << ":" << h->v.val->toString() << std::endl;
        handle.Insert(h);
    }
    key = "wode";
    for (int i = 0; i < 10; ++i) {
        string key2 = key + to_string(i);
        Robj* s = new Robj(key2);
        Entry *tmp = handle.Lookup(s);
        std::cout << tmp->key->toString() << ":" << tmp->v.val->toString() << std::endl;
    }

}
