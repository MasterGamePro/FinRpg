#pragma once

#include <string>
#include "fin/debug/exception.h"

namespace fin::stream {
  template <typename T>
  class IInputStream {
    public:
    virtual ~IInputStream() {
      close();
      // TODO: Log if forgot to close stream.
      /*if (!is_closed_) {
        throw debug::Exception("IInputStream", "~IInputStream", "Stream was not closed.");
      }*/
    }

    int available() {
      if (is_closed_) {
        throw debug::Exception("IInputStream", "available", "Stream is closed.");
      }
      return on_available();
    }

    void close() {
      is_closed_ = true;
      on_close();
    }

    T read() {
      if (is_closed_) {
        throw debug::Exception("IInputStream", "read", "Stream is closed.");
      }
      return on_read_single();
    }

    void read(T* destinationArray, const int count) {
      read(destinationArray, 0, count);
    }

    void read(T* destinationArray, const int offset, const int count) {
      if (is_closed_) {
        throw debug::Exception("IInputStream", "read", "Stream is closed.");
      }
      on_read_multiple(destinationArray, offset, count);
    }

    protected:
    virtual int on_available() = 0;
    virtual void on_close() = 0;
    virtual T on_read_single() = 0;
    virtual void on_read_multiple(T* destinationArray, int offset, int count) = 0;

    private:
    bool is_closed_ = false;
  };
}
