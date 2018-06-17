#pragma once

#include <string>

namespace fin::common::string {
  int index_of(const std::string& str, char c) {
    return index_of(str::begin(), str::end(), c);
  }

  int index_of(const std::string::const_iterator& start,
               const std::string::const_iterator& end, char c) {
    return 
  }
}
