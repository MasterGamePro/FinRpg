#include "stdafx.h"

#include <GL/glew.h>

#include "fin/debug/log.h"
#include "fin/graphics/texture.h"

#include "texture/imagetextureutil.h"

#include "texturesgl.h"

namespace fin::graphics {
  TexturesGl::TexturesGl() {
    cached_file_textures_.set_miss_handler([this](io::File file) {
      cimg_library::CImg<unsigned char> img(file.get_path().c_str());
      return create_texture_from_image(img.normalize(0, 255));
    });
  }

  void TexturesGl::bind(const Texture& texture) {
    const auto textureId = static_cast<GLuint*>(texture.
      get_internal_data());
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *textureId);
  }

  void TexturesGl::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
  }

  Texture TexturesGl::load_texture(const io::File& file) {
    return cached_file_textures_[file];
  }

  Texture TexturesGl::create_texture_from_image(
    cimg_library::CImg<unsigned char> img) {
    unsigned int id;
    glGenTextures(1, &id);

    copy_image_into_id(img, id, true);

    Texture texture;
    set_texture_id(texture, id);

    return texture;
  }

  void TexturesGl::reload_context() {
    for (auto pair : cached_file_textures_) {
      const auto file = pair.first;
      const auto image = pair.second;
      const auto textureId = static_cast<GLuint*>(image.
        get_internal_data());
      load_image_into_id(file, *textureId);
    }
  }

  void TexturesGl::set_texture_id(Texture& texture, const GLuint textureId) {
    texture.set_internal_data(new GLuint(textureId));
  }

  GLuint TexturesGl::get_texture_id(Texture& texture) const {
    return *static_cast<GLuint*>(texture.get_internal_data());
  }
}
