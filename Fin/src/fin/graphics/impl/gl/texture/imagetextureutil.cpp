#include "stdafx.h"
#include "imagetextureutil.h"

namespace fin::graphics {
  void copy_image_into_id(cimg_library::CImg<unsigned char> img,
                          const GLuint id, bool shouldRepeat) {
    int width = img.width(), height = img.height();

    glBindTexture(GL_TEXTURE_2D, id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    const auto edgeBehavior = shouldRepeat ? GL_REPEAT : GL_CLAMP;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, edgeBehavior);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, edgeBehavior);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    auto i = 0;
    const auto numChannels = img.spectrum();
    unsigned char* out = nullptr;
    int imgType = GL_RGB;

    if (numChannels == 1) {
      imgType = GL_RGB;
      out = new unsigned char[width * height * 3];
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          unsigned int v = img(x, y, 0);
          for (int c = 0; c < 3; c++) { out[i++] = v; }
        }
      }
    }
    else if (numChannels == 2) {
      imgType = GL_RGBA;
      out = new unsigned char[width * height * 4];
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          unsigned int v = img(x, y, 0);
          for (int c = 0; c < 3; c++) { out[i++] = v; }
          out[i++] = img(x, y, 1);
        }
      }
    }
    else if (numChannels == 3) {
      imgType = GL_RGB;
      out = new unsigned char[width * height * 3];
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          for (int c = 0; c < 3; c++) { out[i++] = img(x, y, c); }
        }
      }
    }
    else if (numChannels == 4) {
      imgType = GL_RGBA;
      out = new unsigned char[width * height * 4];
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          for (int c = 0; c < 4; c++) { out[i++] = img(x, y, c); }
        }
      }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, imgType, width, height, 0, imgType,
                 GL_UNSIGNED_BYTE, out);
    delete[] out;

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
  }

  void load_image_into_id(const io::File& file, const GLuint id) {
    cimg_library::CImg<unsigned char> img(file.get_path().c_str());
    copy_image_into_id(img.normalize(0, 255), id, true);
  }
}
