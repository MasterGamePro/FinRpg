#include <json/json.h>
#include "util.h"

namespace rpg::save {
  bool read_options_from_file(Options& options, const fin::io::File& file) {
    if (file.exists()) {
      std::ifstream ifs(file.get_path());
      Json::Reader reader;
      Json::Value optionsJson;
      // TODO: Gracefully handle error in parsing.
      reader.parse(ifs, optionsJson);

      const auto resolution = optionsJson["resolution"];
      options.set_resolution(resolution[0].asUInt(), resolution[1].asUInt());

      const auto isFullscreen = optionsJson["isFullscreen"].asBool();
      options.toggle_fullscreen(isFullscreen);

      return true;
    }
    return false;
  }

  void write_options_to_file(const Options& options,
                             const fin::io::File& file) {
    Json::Value optionsJson;
    Json::Value resolution;

    resolution[0] = options.get_width();
    resolution[1] = options.get_height();
    optionsJson["resolution"] = resolution;

    optionsJson["isFullscreen"] = options.is_fullscreen();

    std::ofstream os(file.get_path());
    Json::FastWriter writer;
    os << writer.write(optionsJson);
  }
}
