#pragma once

#include "ifilesystemelement.h"

namespace fin::io {
  class File : public IFilesystemElement {
  public:
    File(const std::string path) : IFilesystemElement(path) {}

    bool operator==(const File& other) const { return path == other.path; }
    bool operator<(const File& other) const { return path < other.path; }
  };
}
