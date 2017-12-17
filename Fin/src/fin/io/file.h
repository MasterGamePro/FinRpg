#pragma once
#include <string>

namespace fin::io {
  class File {
  public:
    File(std::string path) {
      this->path = path;
    }

    std::string get_path() const { return path; }
    bool exists() const {
      struct stat buffer;
      return (stat(path.c_str(), &buffer) == 0);
    }

  private:
    std::string path;
  };
}
