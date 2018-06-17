#pragma once

namespace fin::app {

  enum class WindowLibrary {
    GLFW
  };

  enum class InputLibrary {
    SDL
  };

  enum class GraphicsLibrary {
    OPENGL,
    DIRECTX
  };

  enum class AudioLibrary {
    SDL,
    OPENAL
  };
}