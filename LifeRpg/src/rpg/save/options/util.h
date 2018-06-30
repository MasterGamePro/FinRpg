#pragma once
#include "fin/io/file.h"
#include "options.h"

namespace rpg::save {
  bool read_options_from_file(Options& options, const fin::io::File& file);
  void write_options_to_file(const Options& options,
                             const fin::io::File& file);
}
