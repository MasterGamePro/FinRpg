#pragma once

namespace fin::app {

  enum WindowLibrary {
    WINDOWLIBRARY_GLFW
  };

  enum InputLibrary {
    INPUTLIBRARY_SDL
  };

  enum GraphicsLibrary {
    GRAPHICSLIBRARY_OPENGL,
    GRAPHICSLIBRARY_DIRECTX
  };

  enum AudioLibrary {
    AUDIOLIBRARY_SDL,
    AUDIOLIBRARY_OPENAL
  };
}