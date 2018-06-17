#pragma once

#include "fin/data/map/missmap.h"

#include "fin/graphics/itextures.h"

namespace fin::graphics {
    class TexturesGl : public ITextures {
    public:
    TexturesGl();

    virtual void bind(const Texture& texture);
    virtual void unbind();

    Texture load_texture(const io::File& file);

    Texture create_texture_from_image(cimg_library::CImg<unsigned char> img)
    override final;

    void reload_context();

    void set_texture_id(Texture& texture, const GLuint textureId);
    GLuint get_texture_id(Texture& texture) const;

    private:
    // TODO: Delete unused textures when their references are lost.
    // TODO: Implement method in this class that deletes a ~'ed Texture.
    data::MissMap<io::File, Texture> cached_file_textures_;
    std::vector<Texture> image_textures_;
  };
}
