#pragma once

#include <exception>
#include <vector>

#include <AL/alc.h>
#include <vorbis/vorbisfile.h>

#include "fin/audio/iaudio.h"
#include "fin/io/file.h"
#include "listeneral.h"

namespace fin::audio {
  class AudioAl : public IAudio {
    public:
    AudioAl() {}

    void init() override final {
      device = alcOpenDevice(nullptr);
      if (!device) {
        throw std::
          exception("Failed to open default audio device for OpenAL.\n");
      }
      context = alcCreateContext(device, nullptr);
      if (!alcMakeContextCurrent(context)) {
        throw std::exception("Failed to make context current.\n");
      }
      listener_ = new ListenerAl();
    }

    void deinit() override final {
      alcDestroyContext(context);
      alcCloseDevice(device);
    }

    IListener* get_listener() override final { return listener_; }

    IBuffer* load(const io::File& file) {
      ALenum format; // The sound data format
      ALsizei freq; // The frequency of the sound data
      std::vector<char> bufferData; // The sound buffer data from file

      // Load the OGG file into memory
      LoadOGG(file.get_path(), bufferData, format, freq);

      // Upload sound data to buffer
      alBufferData(bufferID, format, &bufferData[0],
                   static_cast<ALsizei>(bufferData.size()), freq);

      // Attach sound buffer to source
      alSourcei(sourceID, AL_BUFFER, bufferID);
    }

    private:
    void LoadOGG(const std::string& fileName, std::vector<char>& buffer,
                 ALenum& format,
                 ALsizei& freq) {
      const int kBufferSize = 32768; // 32kb
      int endian = 0; // 0 for Little-Endian, 1 for Big-Endian
      int bitStream;
      long bytes;
      char array[kBufferSize]; // Local fixed size array
      FILE* f;

      // Open for binary reading
      f = fopen(fileName.c_str(), "rb");

      if (f == NULL) {
        std::cerr << "Cannot open " << fileName << " for reading..." << std::
          endl;
        exit(-1);
      }
      // end if

      vorbis_info* pInfo;
      OggVorbis_File oggFile;

      // Try opening the given file
      if (ov_open(f, &oggFile, NULL, 0) != 0) {
        std::cerr << "Error opening " << fileName << " for decoding..." << std::endl;
        exit(-1);
      }

      // Get some information about the OGG file
      pInfo = ov_info(&oggFile, -1);

      // Check the number of channels... always use 16-bit samples
      if (pInfo->channels == 1) { format = AL_FORMAT_MONO16; }
      else { format = AL_FORMAT_STEREO16; }

      // The frequency of the sampling rate
      freq = pInfo->rate;

      // Keep reading until all is read
      do {
        // Read up to a buffer's worth of decoded sound data
        bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);

        if (bytes < 0) {
          ov_clear(&oggFile);
          std::cerr << "Error decoding " << fileName << "..." << endl;
          exit(-1);
        }

        // Append to end of buffer
        buffer.insert(buffer.end(), array, array + bytes);
      }
      while (bytes > 0);

      // Clean up!
      ov_clear(&oggFile);
    }

    ALCdevice* device;
    ALCcontext* context;
    ListenerAl* listener_;
  };
}
