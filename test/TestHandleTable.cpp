#include<string>
#include<iostream>
#include"Entry.h"
#include"HandleTable.h"

using namespace std;
using namespace emcache;

int main() {

    HandleTable handle(1.0);
    string key = "wode";
    string value = "val";

    for(int i = 0; i < 10000; ++i) {
        string key1 = key + to_string(i);
        string value1 = value + to_string(i);
        Entry *h = new Entry(key1, value1);
        handle.Insert(h);
    }
    key = "wode";
    for (int i = 0; i < 10; ++i) {
        string key2 = key + to_string(i);
        Robj* s = new Robj(key2);
        Entry *tmp = handle.Lookup(s);
        std::cout << tmp->key->toString() << ":" << tmp->v.val->toString() << std::endl;
    }

    for (int i = 1000; i< 10000; ++i) {
        string key2 = key + to_string(i);
        Robj* s = new Robj(key2);
        Entry* tmp = handle.Remove(s);
        if (tmp) {
            std::cout << tmp->key->toString() << ":" << tmp->v.val->toString() << std::endl;
            delete tmp;
        }
    }
    string s2 = "wode125";
    Robj *s3 = new Robj(s2);
    Entry *tmp = handle.Lookup(s3);
    std::cout << tmp->v.val->toString() << std::endl;

}