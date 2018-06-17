#pragma once

namespace fin::data {
  template <typename T>
  class cache_ptr {
    public:
    explicit cache_ptr(T* ptr) : ptr_(ptr) {
      count_ = new int;
      *count_ = 1;
    }

    cache_ptr(const cache_ptr<T>& other) {
      ptr_ = other.ptr_;
      count_ = other.count_;
    }

    ~cache_ptr() {
      // If count is 1, then only stored in the cache map.
      if (--(*count_) == 1) {
        delete ptr_;
        delete count_;
      }
    }

    int use_count() const { return *count_; }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }

    private:
    T* ptr_;
    int* count_;
  };
}
