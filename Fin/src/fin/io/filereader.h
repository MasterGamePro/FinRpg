#pragma once
#pragma once

#include "file.h"
#include "fin/stream/iinputstream.h"

namespace fin::io {
  class FileReader : stream::IInputStream {
    public:
    FileReader( File file ) : file( file ) {
      
    }

    char read_char() override {
      return 
    }
    std::string read_all_and_close() {
      std::ifstream t( file.get_path() );
      std::string str( ( std::istreambuf_iterator<char>( t ) ),
                       std::istreambuf_iterator<char>() );
      return str;
    }

    private:
    File file;
  };
}
