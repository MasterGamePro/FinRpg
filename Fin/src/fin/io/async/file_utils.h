#pragma once
#include <functional>
#include "fin/async/promise/promise.h"
#include "fin/io/file.h"

namespace fin::io::async {
  async::Promise<std::string> read_as_string(const File& file) {
    return new async::Promise([file](std::function resolve) {
      std::ifstream ifs(file.get_path());
      std::string str((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());
      d.resolve(str);
    });
  }

  async::Promise<std::vector<unsigned char>> read_as_bytes(const File& file) {
    return promise::newPromise([file](promise::Defer d) {
      std::ifstream ifs(filename, ios::binary | ios::ate);
      ifstream::pos_type pos = ifs.tellg();

      std::vector<char>  result(pos);

      ifs.seekg(0, ios::beg);
      ifs.read(&result[0], pos);

      d.resolve(result);
    });
  }
}