#pragma once
#include "file.h"

namespace fin::io {
  class FileWriter {
    public:
    FileWriter( File file ) : file( file ) {}

    private:
    File file;
  };
}
