#pragma once
#include "lib/cimg/CImg.h"
#include "fin/io/file.h"

namespace fin::graphics {
  class ImageTexture {
    public:
    ImageTexture( const io::File& file ) {
      cimg_library::CImg<unsigned char> img( file.get_path().c_str() );

      //img
    }

    void set_data()
    {
      
    }
  };
}
