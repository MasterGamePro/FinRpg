#pragma once

#include <string>
#include <boost/asio/ip/tcp.hpp>

#include "fin/stream/iinputstream.h"
#include "url.h"

namespace fin::web {
  class DownloadStream : stream::IInputStream<uint8_t> {
    public:
    DownloadStream(const Url& uri) {
      const auto host = uri.get_host();
      const auto http = uri.get_scheme();

      stream.connect(host, http);
      stream << "GET " << uri.get_path() << " HTTP/1.1\r\n";
      stream << "Host: " << host << "\r\n";
      stream << "Cache-Control: no-cache\r\n";
      stream << "Connection: close\r\n\r\n" << std::flush;
    }
    
    protected:
    int on_available() {
      
    }

    virtual void on_close() = 0;
    virtual T on_read_single() = 0;
    virtual void on_read_multiple(T* destinationArray, int offset, int count) = 0;

    private:
    boost::asio::ip::tcp::iostream stream;
  };
}
