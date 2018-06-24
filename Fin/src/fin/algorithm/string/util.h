#pragma once

#include <string>
#include <vector>

namespace fin::common::string {
  /*int index_of(const std::string& str, char c) {
    return index_of(str::begin(), str::end(), c);
  }

  int index_of(const std::string::const_iterator& start,
               const std::string::const_iterator& end, char c) {
    return 
  }*/

  // TODO: Switch to string view?
  std::vector<std::string> split(const std::string& str,
                                 const std::string& delimeter) {
    std::vector<std::string> parts;
    const auto delimeterSize = delimeter.size();
    auto size = str.size();
    auto start = 0;
    do {
      // Find next instance of delimeter.
      auto end = str.find(delimeter, start);
      if (end == -1) { end = str.size(); }
      const auto len = end - start;
      if (len > 0) { parts.push_back(str.substr(start, len)); }
      start = end + delimeterSize;
    } while (start < size);
    return parts;
  }
}
