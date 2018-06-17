#pragma once

#include <functional>
#include <map>

#include "cacheptr.h"

namespace fin::data {
  template <typename K, typename V>
  class CacheMap {
    public:
    cache_ptr<V> operator[](K key) {
      auto it = map_.find(key);
      if (it != map_.end()) { return *it; }
      auto value = miss_handler_(key);
      auto cachedValue = cache_ptr<V>(value);
      map_[key] = cachedValue;
      return cachedValue;
    }

    void set_miss_handler(std::function<V(K)> miss_handler) {
      miss_handler_ = miss_handler;
    }

    //void clear() { map_.clear(); }

    void refresh() {
      for (auto it = map_.cbegin(); it != map_.cend();) {
        if (it->use_count() == 1) { it = map_.erase(it); }
        else { ++it; }
      }
    }

    private:
    std::map<K, cache_ptr<V>> map_;
    std::function<V(K)> miss_handler_;
  };
}
