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
    // TODO: Use assert or exception to enforce proper mi/ma values?
    return max(mi, min(x, ma));
  }

  template<typename T>
  T wrap(T mi, T x, T ma) {
    // TODO: Use assert or exception to enforce proper mi/ma values?
    const T diff = ma - mi,
      mod = (x - mi) % diff;
    return mi + mod;
  }

  template<typename T>
  T pow(T x, T n) {
    return std::pow(x, n);
  }

  template<typename T>
  T sqr(T x) {
    return x * x;
  }

  template<typename T>
  T sqrt(T x) {
    return std::sqrt(x);
  }

  template<typename T>
  T interpolate(T mi, T ma, T frac) {
    // TODO: Use assert or exception to enforce proper mi/ma values?
    return mi + (ma - mi) * frac;
  }

  template<typename T>
  T floor(T x) {
    return std::floor(x);
  }

  template<typename T>
  T ceil(T x) {
    return std::ceil(x);
  }

  template<typename T>
  T round(T x) {
    return std::round(x);
  }

  template<typename T>
  T round_to_nearest(T x, T n) {
    return n * round(x / n);
  }

  template<typename T>
  T round_to_precision(T x, T n) {
    // TODO: Is .1 right?
    return round_to_nearest(x, pow(.1, n));
  }
}