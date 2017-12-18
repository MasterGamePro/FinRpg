#pragma once

#include "ifilesystemelement.h"

namespace fin::io {
  class Directory : public IFilesystemElement {
  public:
    Directory(const std::string path) : IFilesystemElement(path) {}

    bool operator==(const Directory& other) const { return path == other.path; }
    bool operator<(const Directory& other) const { return path < other.path; }
  };
}
