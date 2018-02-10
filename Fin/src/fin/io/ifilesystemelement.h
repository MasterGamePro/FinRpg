#pragma once

#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#include <boost/filesystem.hpp>

namespace fin::io {
  class Directory;

  class IFilesystemElement {
    public:
    IFilesystemElement(const std::string path) {
      this->path = boost::filesystem::path(path);
    }
    virtual ~IFilesystemElement() {}

    std::string get_path() const { return path.string(); }

    Directory parent() const;

    bool exists() const { return boost::filesystem::exists(path); }
    int size() const { return path.size(); }

    protected:
    boost::filesystem::path path;
  };
}
