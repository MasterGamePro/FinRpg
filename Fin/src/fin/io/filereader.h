#pragma once
#pragma once
#include "file.h"

namespace fin::io {
  class FileReader {
    public:
    FileReader( File file ) : file( file ) {}

    std::string read_all() {
      std::ifstream t( file.get_path() );
      std::string str( ( std::istreambuf_iterator<char>( t ) ),
                       std::istreambuf_iterator<char>() );
      return str;
    }

    private:
    File file;
  };
}
