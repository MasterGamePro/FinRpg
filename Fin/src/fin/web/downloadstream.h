#pragma once

#include <string>
#include "fin/stream/iinputstream.h"

namespace fin::web {
  class DownloadStream : stream::IInputStream<uint8_t> {
    public:
    DownloadStream(std::string uri) {
      
    }
  };
}
