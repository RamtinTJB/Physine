#ifndef PHYSINE_UTILS_H_
#define PHYSINE_UTILS_H_

#include <unordered_map>

template <class K, class V>
bool map_contains(const std::unordered_map<K, V>& map, const K& key) {
    return map.count(key) >= 1;
}

#endif
