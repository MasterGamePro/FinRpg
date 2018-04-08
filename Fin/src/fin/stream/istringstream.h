#pragma once

#include <string>
#include "fin/debug/exception.h"

namespace fin::stream {
  class IInputStream {
    public:
    virtual ~IInputStream() {
      if (!is_closed_) {
        throw debug::Exception("IInputStream", "~IInputStream", "Stream was not closed.");
      }
    }

    char read_char() {
      if (is_closed_) {
        throw debug::Exception("IInputStream", "read_char", "Stream is closed.");
      }
      return on_read_char();
    }

    std::string read_chars(int count) {
      if (is_closed_) {
        throw debug::Exception("IInputStream", "read_chars", "Stream is closed.");
      }
      return on_read_chars(count);
    }

    virtual std::string read_line() {
      if (is_closed_) {
        throw debug::Exception("IInputStream", "read_line", "Stream is closed.");
      }
      return on_read_line();
    }

    virtual void close() = 0;

    protected:
    virtual char on_read_char() = 0;
    virtual std::string on_read_chars(int count);
    virtual std::string on_read_line() = 0;
    virtual std::string on_read_all_and_close() = 0;

    private:
    bool is_closed_ = false;
  };
}
