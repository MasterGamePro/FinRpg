#pragma once

#include <GL/glew.h>
#include "../../itextures.h"

namespace fin::graphics {
  class TexturesGl : public ITextures {
    public:
    virtual void bind(ITexture* texture) {
      if (texture != nullptr) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture->get_id());
      }
      else {
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
      }
    }

    ImageTexture * create_texture_from_image(cimg_library::CImg<unsigned char> img) override final {
      int width = img.width(), height = img.height();
      unsigned int id;

      glGenTextures(1, &id);
      glBindTexture(GL_TEXTURE_2D, id);
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

      int i = 0, numChannels = img.spectrum();
      debug::Log::println("Channels: %d", numChannels);
      unsigned char *out = nullptr;
      int imgType = GL_RGB;

      if (numChannels == 1) {
        imgType = GL_RGB;
        out = new unsigned char[width * height * 3];
        for (int y = 0; y < height; y++) {
          for (int x = 0; x < width; x++) {
            unsigned int v = img(x, y, 0);
            for (int c = 0; c < 3; c++) {
              out[i++] = v;
            }
          }
        }
      }
      else if (numChannels == 2) {
        imgType = GL_RGBA;
        out = new unsigned char[width * height * 4];
        for (int y = 0; y < height; y++) {
          for (int x = 0; x < width; x++) {
            unsigned int v = img(x, y, 0);
            for (int c = 0; c < 3; c++) {
              out[i++] = v;
            }
            out[i++] = img(x, y, 1);
          }
        }
      }
      else if (numChannels == 3) {
        imgType = GL_RGB;
        out = new unsigned char[width * height * 3];
        for (int y = 0; y < height; y++) {
          for (int x = 0; x < width; x++) {
            for (int c = 0; c < 3; c++) {
              out[i++] = img(x, y, c);
            }
          }
        }
      }
      else if (numChannels == 4) {
        imgType = GL_RGBA;
        out = new unsigned char[width * height * 4];
        for (int y = 0; y < height; y++) {
          for (int x = 0; x < width; x++) {
            for (int c = 0; c < 4; c++) {
              out[i++] = img(x, y, c);
            }
          }
        }
      }

      glTexImage2D(GL_TEXTURE_2D, 0, imgType, width, height, 0, imgType, GL_UNSIGNED_BYTE, out);
      delete[] out;

      return new ImageTexture(id, width, height);
    }
  };
}