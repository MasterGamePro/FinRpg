#pragma once

#define cimg_use_bmp
#define cimg_use_jpeg
#define cimg_use_png
#include <CImg.h>

#include <GL/glew.h>

#include "fin/io/file.h"

namespace fin::graphics {
  void copy_image_into_id(cimg_library::CImg<unsigned char> img,
                          const GLuint id, bool shouldRepeat);
  void load_image_into_id(const io::File& file, const GLuint id);
}
