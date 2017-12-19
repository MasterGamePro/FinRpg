#pragma once

#include <string>

namespace fin::stream {
  class IInputStream {
    public:
    virtual char read_char() = 0;
    virtual std::string read_chars( int count ) = 0;
    virtual std::string read_line() = 0;
  };
}