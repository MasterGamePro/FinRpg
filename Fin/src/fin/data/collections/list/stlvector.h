#pragma once

#include <vector>
#include "ilist.h"
#include "fin/debug/exception.h"

namespace fin::data {
  template <typename T>
  class StlVector : public IList<T> {
    public:

    virtual ~StlVector() { clear(); }

    T& at(const int index) override final { return list_.at(index); }
    const T& at(const int index) const override final {
      return list_.at(index);
    }

    T& front() override final {
      if (size() > 0) { return list_.front(); }
      throw debug::Exception("StlVector", "front", "The list is empty.");
    }

    const T& front() const override final {
      if (size() > 0) { return list_.front(); }
      throw debug::Exception("StlVector", "front", "The list is empty.");
    }

    T& back() override final {
      if (size() > 0) { return list_.back(); }
      throw debug::Exception("StlVector", "back", "The list is empty.");
    }

    const T& back() const override final {
      if (size() > 0) { return list_.back(); }
      throw debug::Exception("StlVector", "back", "The list is empty.");
    }

    void insert_before(int index, const T& t) override final {
      list_.insert(list_.begin() + index, t);
    }
    void insert_after(int index, const T& t) override final {
      list_.insert(list_.begin() + index + 1, t);
    }
    void remove_at(int index) override final {
      list_.erase(list_.begin() + index);
    }

    void push_back(const T& t) override final { list_.push_back(t); }

    bool pop_back() override final {
      auto si = size();
      if (si > 0) {
        list_.pop_back();
        return true;
      }
      return false;
    }

    void clear() override final { list_.clear(); }
    int size() const override final { return list_.size(); }

    // TODO: Add begin/end.
    /*
    template <
      class Value,
      class CategoryOrTraversal,
      class Reference = Value &,
      class Difference = std::ptrdiff_t
    >
    class any_iterator;

    typedef any_iterator<
      T,
      boost::bidirectional_traversal_tag
    > t_iterator;

    typedef any_iterator<
      T const,
      boost::bidirectional_traversal_tag
    > const_t_iterator;

    t_iterator begin() { return list_.begin(); }
    t_iterator end() { return list_.end(); }
    const_t_iterator begin() const { return list_.cbegin(); }
    const_t_iterator end() const { return list_.cend(); }*/

    void iterate(const std::function<void(T& t, int i)>& lambda) override
    final {
      auto i = 0;
      for (auto t : list_) { lambda(t, i++); }
    }

    void const_iterate(
      const std::function<void(const T& t, int i)>& lambda) const override
    final {
      auto i = 0;
      for (const auto t : list_) { lambda(t, i++); }
    }


    private:
    std::vector<T> list_;
  };
}
