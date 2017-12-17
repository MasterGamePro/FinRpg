#pragma once
#include <string>

namespace fin::io {
  class File {
    public:
    File( std::string path ) {
      this->path = path;
    }

    std::string get_path() const { return path; }

    private:
    std::string path;
  };
}
