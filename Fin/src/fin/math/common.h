#pragma once

namespace fin::math {
  template<typename T>
  T min(T lhs, T rhs) {
    return lhs < rhs ? lhs : rhs;
  }

  template<typename T>
  T max(T lhs, T rhs) {
    return lhs > rhs ? lhs : rhs;
  }

  template<typename T>
  T contain(T mi, T x, T ma) {
    return max(mi, min(x, ma));
  }
}