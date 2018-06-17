#pragma once

#include <functional>
#include <map>

namespace fin::data {
  template <typename K, typename V>
  class MissMap {
    public:
    V operator[](K key) {
      const auto it = map_.find(key);
      if (it != map_.end()) { return it->second; }
      auto value = miss_handler_(key);
      map_[key] = value;
      return value;
    }

    void set_miss_handler(std::function<V(K)> miss_handler) {
      miss_handler_ = miss_handler;
    }

    void clear() {
      map_.clear();
    }

    typename std::map<K, V>::iterator begin() {
      return map_.begin();
    }
    typename std::map<K, V>::iterator end() {
      return map_.end();
    }

    private:
    std::map<K, V> map_;
    std::function<V(K)> miss_handler_;
  };
}
