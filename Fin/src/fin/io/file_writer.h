#pragma once

#include "file.h"
#include "fin/stream/ioutputstream.h"

namespace fin::io {
  class FileWriter : stream::IOutputStream {
    public:
    FileWriter( File file ) : file( file ) {}
    
    private:
    File file;
  };
}

